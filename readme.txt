Spam Email Filter (C Project)

Description:
This project implements a spam email detection program in C. It reads an email’s content from the user and checks it against a list of predefined spam keywords. If any spam keywords are found, the program says the email as spam else not spam.

The program uses a hash table with linked lists to store spam words efficiently, allowing fast lookup even with collisions. It also handles case-insensitive word matching and dynamically processes the input text.

Data Structures Used:
- Hash Table with chaining (linked lists) to store and search spam keywords efficiently.
- Linked Lists to handle hash collisions.
- Dynamic arrays to extract words from email content.

Requirements:
- C compiler supporting C99 or later (e.g., GCC). 
- Terminal or command prompt for running the program.

How to Compile and Run:
1. Compile the source code:
   gcc -o spamfilter spamfilter.c

2. Run the executable:
   ./spamfilter

3. When prompted, enter or paste the email content and press Enter.

4. The program will display “result: spam” if spam words are detected, or “result: not spam” otherwise.

Notes:
- The list of spam keywords is hardcoded but can be modified by editing the `spamlist` array in the source code.
- The program reads the entire email content at once, so very large emails may require increased memory limits.
- This is a simple demonstration projet.



