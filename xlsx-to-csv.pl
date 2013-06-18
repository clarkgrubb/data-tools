#!/usr/bin/env perl

use File::Spec;
use Getopt::Long;
use Spreadsheet::XLSX;
use Text::CSV;
use Text::Iconv;

package CSVWriter;

sub new {
  my $class = shift;
  my $path = shift;
  my $csv = Text::CSV->new({binary=>1, eol=>$\})
    or die "Text::CSV->new() failed: " . Text::CSV->error_diag();
  my $file_handle;
  my $eol = "\r\n";

  open $file_handle, ">:encoding(utf8)", $path
    or die "could not open $path for writing: $!";

  my $self = {path=>$path,
              csv=>$csv,
              file_handle=>$file_handle,
              eol=>$eol};

  bless $self, $class;
  $self;
}

sub print_row {
  my $self = shift;
  my $arrayref = shift;

  $self->{csv}->print($self->{file_handle}, $arrayref)
    or die "CSV write failure";

  my $f = $self->{file_handle};
  print $f $self->{eol};
}

sub close {
  my $self = shift;
  close $self->{file_handle}
    or die "error closing $self->{path}: $!";
}

package ::;

sub mkdir_or_die {

  my $dir = shift;

  if (!mkdir($dir)) {
    if (-d $dir) {
      die "directory already exists: $dir";
    }
    die "failed to create directory: $dir";
  }
}

sub open_xlsx {

  my $xlsx_path = shift;

  my $converter = Text::Iconv->new("utf-8", "windows-1251");
  my $xlsx = Spreadsheet::XLSX->new($xlsx_path, $converter);

  $xlsx;
}

sub safe_filename {

  $name = shift;
  $name =~ s/ /_/g;
  $name =~ s/[^a-z1-9_]//gi;

  $name;
}

sub safe_dir_and_filename {
  my $dir = shift;
  my $sheet_name = shift;
  my $safe_name = safe_filename($sheet_name);
  my $path = File::Spec->catfile($dir, $safe_name) . ".csv";

  return $path;
}

sub xlsx_row_as_arrayref {
  my $sheet = shift;
  my $row = shift;

  my @fields;

  foreach my $col ($sheet->{MinCol} ..  $sheet->{MaxCol}) {
    push @fields, $sheet->{Cells}[$row][$col]->{Val};
  }

  return \@fields;
}

sub set_sheet_limits {
  $sheet = shift;
  $sheet->{MaxRow} ||= $sheet->{MinRow};
  $sheet->{MaxCol} ||= $sheet->{MinCol};
}

sub list_sheets {
  my $xlsx_path = shift;

  # Archive::Extract module must extract the files
  # to list them.  Calling the external tool unzip
  # avoids creating files.
  #
  my @lines = qx(unzip -l $xlsx_path);

  for $line (@lines) {

    if ($line =~ /xl\/worksheets\/(.+)\.xml/i) {

      my $sheet = $1;
      @fields = split(/\s+/, $line);
      my $size = $fields[1];
      print "$sheet $size\n";
    }
  }
}

sub xlsx_to_csv {

  my $xlsx_path = shift;
  my $output_dir_or_file = shift;
  my $sheet_to_dump = shift;

  if (!$sheet_to_dump) {
    mkdir_or_die($output_dir_or_file);
  }

  my $xlsx = open_xlsx($xlsx_path);

  foreach my $sheet (@{$xlsx->{Worksheet}}) {

    if ($sheet_to_dump && (lc($sheet_to_dump) ne lc($sheet->{Name}))) {
      next;
    }

    set_sheet_limits($sheet);
    if ($sheet_to_dump) {
      $csv_writer = CSVWriter->new($output_dir_or_file);
    }
    else {
      $csv_path = safe_dir_and_filename($output_dir_or_file,
                                        $sheet->{Name});
      $csv_writer = CSVWriter->new($csv_path);
    }

    foreach my $row ($sheet->{MinRow} .. $sheet->{MaxRow}) {

      $fields = xlsx_row_as_arrayref($sheet, $row);
      $csv_writer->print_row($fields);
    }
    $csv_writer->close();

    if ($sheet_to_dump) {
      last;
    }
  }
}


# TODO:
#
# options: don't remove spaces from sheet names
# only extract one sheet (option to specify it)
# just list sheet names
# change line ending
# safe file name code can give two different sheets
# the same name!  Code probably silently overwrites!

my ($list, $encoding, $sheet, $help);

my $usage =
  "USAGE: $0 [--encoding=ENCODING] INPUT_FILE OUTPUT_DIR\n" .
  "       $0 [--encoding=ENCODING] --sheet=SHEET INPUT_FILE [OUTPUT_FILE]\n" .
  "       $0 --list INPUT_FILE\n" .
  "       $0 --help\n";

if (!Getopt::Long::GetOptions("list" => \$list,
                              "encoding" => \$encoding,
                              "sheet=s" => \$sheet,
                              "help" => \$help)
    || $help) {

  print $usage;
  exit 1;
}

if ($list) {
  if ($#ARGV != 0) {
    print("one argument is required\n");
    print $usage;
    exit 1;
  }
  list_sheets($ARGV[0]);
  exit 0;
}

if ($#ARGV != 1) {
  print "two arguments are required\n";
  print $usage;
  exit 1;
}

xlsx_to_csv($ARGV[0], $ARGV[1], $sheet);
