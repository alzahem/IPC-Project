
351-03, Spring 2021
## Program written in C++

# Group Members:
    Kevin Espinoza -- k.espinoza1012@csu.fullerton.edu
    Ernesto Hooghkirk -- ernesto_hooghkirk@csu.fullerton.edu
    Maria Medina -- rosemary98@csu.fullerton.edu
    Phillip Presuel -- phillipp@csu.fullerton.edu
    Mohammad Alzahem -- alzahem@csu.fullerton.edu

How to execute your program:
    Using linux complete the following steps,
    Run `make` in the terminal while accessing the location of this project file directory.
    Run `./recv` in that same terminal.
    The terminal should now display the following output as it waits for sender to send a message:
![image](https://user-images.githubusercontent.com/37064367/116765075-46282c00-a9d8-11eb-9ba5-d32b89c97be8.png)

    Then run `./sender keyfile.txt` in a a separate terminal while accessing the location of this project file directory.
    That terminal will now display the following:
![image](https://user-images.githubusercontent.com/37064367/116765068-40cae180-a9d8-11eb-891c-11f67f909c9c.png)

    The terminal where `./recv` was run should now display the following:
![image](https://user-images.githubusercontent.com/37064367/116765062-3872a680-a9d8-11eb-841c-f7a5cd3f6e6a.png)

    The contents of the file sent as a message from `keyfile.txt` will then be copied into `recv`
    Run `make clean` in the terminal to remove .o files created by `make`.

Whether you implemented the extra credit:
    Our team did not complete the extra credit.
Anything special about your submission that we should take note of:
