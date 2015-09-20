
# csv-delim

  Delimininate a csv file

## Usage

  Convert csv to tsv quickly

    $ csv-delim < in.csv > out.tsv

  Some custom input delimination

    $ csv-delim -i '|' < in.psv > out.tsv

  Some custom output delimination

    $ csv-delim -d '|' < in.csv > out.psv

## Examples

### csv pretty printer

    $ csv-column () { csv-delim < "$1" | column -t -s $'\t' | less -S }

### csv grep

    $ csv-delim < in.csv | awk -F $'\t' '$3 == "match me"'

### csv cut

    $ csv-cut () { cmd="$1"; shift; csv-delim < "$CMD" | cut -d $'\t' "$@" }

## Why

  I started writing a bunch of [csv tools](https://github.com/jb55/csv-tools)
  but then I realized it's against the unix philosophy. Instead of csv-cut you
  can do:

    $ csv-delim < in.csv | cut -d $'\t' -f 2,3

  and instead of csv-grep you can do:

    $ csv-delim < in.csv | awk -F $'\t' '$3 == "match me"'

  Maybe use these aliases to make this a bit nicer:

    $ alias cutt="cut -d $'\t'"
    $ alias awkt="awk -F $'\t'"

