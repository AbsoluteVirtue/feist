# Disclaimer
A toy example of a working Feistel cypher, please don't use it for any kind of cryptographic applications.

Compiled with g++ ver. 8.1.0 using MinGW-W64 GCC port, with c++17 flag enabled. 

# Description
0. Preliminary steps include splitting plaintext into two halves (L1 and R1), with the private key also split into two halves of corresponding lengths (K1 and K2). 
1. First round consists of obtaining the function **f1** by applying the exclusive-or (*XOR*) operation on the left half of the private key (K1) and the right half of the payload (R1):

f1 = xor(R1, K1)

2. By XORing the function obtained in the previous step with the left part of the payload (L1) a new value is produced. It will serve as input for the next step of obtaining the function **f2**:

R2 = xor(f1, L1)

L2 = R1

f2 = xor(R2, K2)

3. Finally, L3 and R3 are concatenated to form the finished ciphertext:

R3 = xor(f2, L2)

L3 = R2

Ciphertext = L3 + R3

4. To decipher the message using the same key (hense the symmetrical nature of the cipher), the same steps are repeated:

L4 = L3

R4 = R3

f3 = xor(L4, K2)

L5 = xor(R4, f3)

R5 = L4

f4 = xor(L5, K1)

L6 = xor(R5, f4)

R6 = L5

Plaintext = L6 + R6

The number of rounds can be deliberately large, but "3" is enough in most cases.

# TODOs

* Make a sensible list of command-line arguments/flags
* Make plaintext parsing from argv account for whitespace characters
* Normalize ciphertext form to exclude non-printable characters
