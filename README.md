# PostgreSQL-RCE-Extensions
## cmd.c
A User Defined function written in C for PostgreSQL Extensions, can be compiled as DLL for RCE on windows machines.
The function accepts a binary name passed as an argument.

Example:

SELECT test("cmd /c  whoami");

The function doesn't return anything, so you have to get creative on how to find the command output. (Ex: redirect it to a file, etc...)

You can find a full walkthrough using this script for achieving RCE on my Medium post: [Emotional Rollercoaster: A Unique Case Study of Bypassing Antivirus and Firewall by Abusing PostgreSQL](https://medium.com/@yousefamery).


## script.py
A python script that can be used alongside the compiled DLL to automate this technique and achieve RCE on Windows machines.

The script uses large objects in PostgreSQL to upload binary files to a server.



## Resorces
Preparing Visual Studio for compiling DLLs might be a little tricky, but you can check  these to help you:
[Here](https://www.2ndquadrant.com/en/blog/compiling-postgresql-extensions-visual-studio-windows/), [Here](https://learn.microsoft.com/en-us/cpp/build/walkthrough-creating-and-using-a-dynamic-link-library-cpp?view=msvc-170#to-add-the-dll-import-library-to-your-project), [Here](https://learn.microsoft.com/en-us/visualstudio/sharepoint/how-to-add-a-resource-file?view=vs-2022), [Here](https://stackoverflow.com/questions/6769760/how-do-files-get-into-the-external-dependencies-in-visual-studio-c), and [Here](https://blog.conan.io/2021/02/10/Dependencies-Visual-Studio-C++-property-files.html).



The cmd.c file is an edit for the original script at [sourceincite](https://github.com/sourceincite/tools/blob/master/pgpwn.c).

The python script is provided by [sourceincite](https://srcincite.io/blog/2020/06/26/sql-injection-double-uppercut-how-to-achieve-remote-code-execution-against-postgresql.html) I just wanted to share it here for easy access.
