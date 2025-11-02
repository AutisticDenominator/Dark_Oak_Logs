Dark Oak Logs or DOL for short is a simple log taking programme for the Windows operating system.
When opened, the user has a command line to their disposal.
There are several commands for your use:
-help
-write
-read
-exit
-encrypt
-decrypt

help:

This command lists all the commands. Pretty self-explanatory.

write:

This command will ask the user for the new log's title and content. After this, it gets the system's time for a timestamp.
After receiving the user's input, the code checks if the directory for the logs has already been created.
The name of this directory is names "DOLlogs" and is created in the C: directory.
If it was already created, it will proceed. If it has not been created yet, it will create it.

Afterwards, DOL will iterate through every already created logs, which have the name "log" + number. 
Upon getting the largest number, it will create a text file with the name: "log" + (largest_number + 1)
The last act of this command is to save the title, timestamp and content into the newly created file.

read:

This command will display all already created logs, their titles and timestamps.
The user will be asked to input the name of the log they want to read and then it will be displayed.

exit:

This command will exit DOL. Fairly simple.

encrypt/decrypt:

The user will once again input the name of the log, they want to tamper with.
Received said input, it will ask us to input once again but this time we will input a password.
Received all necessary input, DOL will encrypt/decrypt the file's text using an algorithm of my own making and then it will save the file encrypted/decrypted.
Note that it doesn't check whether or not the decryption was to an actual readable text.(if you use wrong password, it doesnt check for that)

DOL was a small side project for me to just create something functional. The encryption algorithm isn't all that complex and safe, so don't rely on it with secret.
And above all it was just a fun project for myself.