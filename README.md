# SimpleFileEncryptor
A simple plaintext file encryption program I wrote in c++.

This was a small program I put together a year or two ago that I had forgotten about. It makes use of a vigenere cipher to encrypt a text file. It isn't anything too complex, but maybe used at a later stage to write a viginere cipher cracking program. DO NOT RELY SOLEY ON THIS PROGRAM FOR SECURITY!!!!!

### Instructions
Assuming your computer has c++ installed, the program can be compiled using the command:

  g++ Encyptor.cpp -o Encrpytor.exe 
  
  To produce an executable for windows. To run the program, use
  
  Encryptor.exe 'your_key' 'e or d' (-enc encrypted_file__name -dec decrypted_file_name -file file_to_encrypt)
  
  All files should be .txt files.
