% RESERVOIR-SAMPLE(1)
% Clark Grubb
% October 13, 2013

# NAME

reservoir-sample - sample lines from file or standard input

# SYNOPSIS

reservoir-sample [-r|--random-seed SEED] (-s NUM|--size=NUM) [FILE]

# DESCRIPTION

Select NUM lines randomly from FILE or standard input.  Each line is equally likely to be chosen.

The script uses reservoir sampling.  It is more efficient than randomly shuffling the file
with `sort -R` and then taking the first N lines with `head`.

To select a sample size which is proportional to the size of the input, use `awk`:

    awk 'rand() < 0.1'

The script allocates memory for N lines of input.

# OPTIONS

-r SEED, \--random-seed=SEED
: a seed value to be passed to the random number generator.

-s NUM, \--size=NUM
: the size of the sample to select

# SEE ALSO

`sort` (1), `awk` (1), `shuf` (1)

https://en.wikipedia.org/wiki/Reservoir_sampling
