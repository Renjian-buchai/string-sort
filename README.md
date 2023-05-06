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
- Cannot be used in conjuction with -L

Flag `-L`:

- Converts string to lowercase
- Cannot be used in conjuction with -U
