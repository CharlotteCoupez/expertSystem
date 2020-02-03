# expertSystem

# The project
coding a expert system for propositional calculus in C++.

Implementation: backward-chaining inference engine.

for more details look at the [Subject](https://cdn.intra.42.fr/pdf/pdf/2029/expert-system.en.pdf)

# Running the tests
```
make
./expersystem [-v] [-o] test/test_file_name.txt
```

# Input file format
```console
# this is a comment$
# all the required rules and symbols, along with the bonus ones, will be
# shown here. spacing is not important
C => E # C implies E
A + B + C => D # A and B and C implies D
A | B => C # A or B implies C
A + !B => F # A and not B implies F
C | !G => H # C or not G implies H
V ^ W => X # V xor W implies X
A + B => Y + Z # A and B implies Y and Z
E + F => !V # E and F implies not V

=ABG # Initial facts : A, B and G are true. All others are false.
# If no facts are initially true, then a simple "=" followed
# by a newline is used
?GVX # Queries : What are G, V and X ?
```
# Options
```
 -v, --verbose		displays investigation steps of the inference engine
 -o, --output		displays the state of all facts
```
