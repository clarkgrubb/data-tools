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
  my $eol = "\n";

  open $file_handle, ">:encoding(utf8)", $path
    or die "could not open $path for wrtiting: $!";

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

  #my $converter = Text::Iconv->new("utf-8", "windows-1251");
  #my $xlsx = Spreadsheet::XLSX->new($xlsx_path, $converter);
  my $xlsx = Spreadsheet::XLSX->new($xlsx_path);

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

  my $xlsx = open_xlsx($xlsx_path);

  foreach my $sheet (@{$xlsx->{Worksheet}}) {
    print $sheet->{Name} . "\n";
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

    if ($sheet_to_dump && ($sheet_to_dump ne $sheet->{Name})) {
      next;
    }

    set_sheet_limits($sheet);
    if ($sheet_to_dump) {
      $csv_writer = CSVWriter->new($output_dir_or_file);
    }
    else {
      $csv_path = safe_dir_and_filename($output_dir_or_file, $sheet->{Name});
      $csv_writer = CSVWriter->new($csv_path);
    }

    foreach my $row ($sheet->{MinRow} .. $sheet->{MaxRow}) {

      $fields = xlsx_row_as_arrayref($sheet, $row);
      $csv_writer->print_row($fields);
    }
    $csv_writer->close();
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

my ($list, $sheet, $help);

my $usage =
  "USAGE: $0 INPUT_FILE OUTPUT_DIR\n" .
  "       $0 --sheet=SHEET INPUT_FILE OUTPUT_FILE\n" .
  "       $0 --list INPUT_FILE\n" .
  "       $0 --help\n";

if (!Getopt::Long::GetOptions("list" => \$list,
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
