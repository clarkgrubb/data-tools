#!/usr/bin/env perl

use File::Spec;
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

sub xlsx_to_csv {

  my $xlsx_path = shift;
  my $output_dir = shift;

  mkdir_or_die($output_dir);

  my $xlsx = open_xlsx($xlsx_path);

  foreach my $sheet (@{$xlsx->{Worksheet}}) {

    set_sheet_limits($sheet);
    $csv_path = safe_dir_and_filename($output_dir, $sheet->{Name});
    $csv_writer = CSVWriter->new($csv_path);

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

if ($#ARGV != 1) {
  die "USAGE: xlsx-to-csv XLSX_FILE DIRECTORY";
}

xlsx_to_csv($ARGV[0], $ARGV[1]);
