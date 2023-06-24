# String Sort

## About this project

Command line application to sort a string by alphabetical order.

## Examples

Sorting a sentence

```ps
C:> strsort.exe The sun is a deadly lazer
```

Output:

```ps
      aaaddeeehillnrsstuyz
```

Sorting a sentence and trimming spaces

```ps
C:> strsort.exe The sun is a deadly lazer -T
```

Output:

```ps
aaaddeeehillnrsstuyz
```

## Possible uses

I don't know, either.

## Flags

Flag `-T`:

- Trims spaces after sorting

Flag `-U`:

- Converts string to uppercase
- Cannot be used in conjuction with `-L`

Flag `-L`:

- Converts string to lowercase
- Cannot be used in conjuction with `-U`

Flag `-F`:

- Takes an input from the file specified by the file path following this flag

Flag `-O`:

- Outputs input to file specified following this flag
- Cannot be used in conjuction with `-o`

Flag `-o`:

- Outputs input to file:
  - `.otttux.txt` if no input file is specified
  - `<sorted filename>.txt` if an input file is specified. The file extension is also sorted.
- Cannot be used in conjuction with `-O`

Flag `-H`:

- Dumps documentation to command line
