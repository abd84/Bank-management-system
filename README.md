# Bank-management-system
  #Structure
- The code starts with the necessary header files and includes several standard libraries for file handling, string manipulation, and vectors.
- The BankSystem class is defined, representing a user account in the bank system. It contains member variables to store user information such as username, password, amount stored, CNIC, date of birth, address, account number, PIN, etc. It also includes member functions for accessing and modifying these variables.
- The Sequence class is a template class that provides functions for adding and withdrawing amounts from a user's account and updating the transaction history.
- The code includes overloaded input and output operators (>> and <<) for the BankSystem class to facilitate input and output operations.
- The loginCode function handles the login process, checks user credentials, and displays user information if the login is successful.
- The operator>> function is used for user registration, where the user provides their information, which is then stored in a file named "Registry.txt".
- The operator<< function is used for user login, where the user enters their username and password. It checks the credentials against the stored user information and sets appropriate flags.
# Functioning 
This code is an implementation of a bank management system. When the code is executed, it prompts the user to either register an account or login. Once registered, it again prompts for login credentials. After entering the correct username and password, which are double-checked, it presents different options based on whether the user wants to create a personal or company account.

The code then provides four options:

Deposit
Withdraw
Check account balance
Logout
These functions are available for both company and user accounts. Additionally, the code saves transaction history in one file and all other client-related information in another file.

However, in company accounts, only bank account users can access the company account. There is also a separate account for the bank CEO, which is predefined and can view all the transactions and account balances of clients, among other details.
