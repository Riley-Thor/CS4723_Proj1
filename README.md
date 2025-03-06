
# AECalculator & MTUHash

This repository contains two C++ programs, `AECalculator.cpp` and `MTUHash.cpp`, which implement a cryptographic hashing function based on a DES-like expansion and S-Box substitution. 
- `MTUHash.cpp`: Implements the `MTUHash` function, a 16-round iterative transformation on a 32-bit input.
- `AECalculator.cpp`: Computes the Avalanche Effect Rate (AFR) by flipping each bit of the input and measuring the hash output differences.

## Compilation
To compile both programs, use g++:

```console
g++ -o MTUHash MTUHash.cpp
```

```console
g++ -o AECalculator AECalculator.cpp
```

## Usage
### Running MTUHash
```console
./MTUHash <input_file>
```

- `<input_file>` should contain a 32-bit binary string.
- Outputs an intermediate hash to `Out1.txt` and final hash to `OutFinal.txt`.

### Running AECalculator
```console
./AECalculator <input_file>
```

- `input_file` should contain a 32-bit binary string.
- Computes the Avalanche Effect Rate (AFR) and writes it to `AFR.txt`.

### Output Files
- `Out1.txt` - Intermediate hash after the first round (from `MTUHash`)
- `OutFinal.txt` - Final hash after 16 rounds (from `MTUHash`)
- `AFR.txt` - Percentage of bit flips in output per bit change (from `AECalculator`)


### Error Handling
- If the input file is missing or incorrect, an error is displayed.
- Input length must be exactly 32 bits; otherwise, a "Length Error" message is shown.

## Authors

Andrew and Riley
