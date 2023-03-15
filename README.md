# PostgreSQL-RCE-Extensions
## cmd.c
A User Defined function written in C for PostgreSQL Extensions, can be compiled as DLL for RCE on windows machines.
The function accepts a binary name passed as an argument.

Example:

SELECT test("cmd /c  whoami");

The function doesn't return anything, so you have to get creative on how to find the command output. (Ex: redirect it to a file, etc...)

You can find a full walkthrough using this script for achieving RCE on my Medium post: [Emotional Rollercoaster: A Unique Case Study of Bypassing Antivirus and Firewall by Abusing PostgreSQL](https://medium.com/@yousefamery/emotional-rollercoaster-a-unique-case-study-of-bypassing-antivirus-and-firewall-by-abusing-2b36d8f6553c).


## script.py
A python script that can be used alongside the compiled DLL to automate the creation of the Database queries and achieve RCE on Windows machines.

The script workes by supplying the OS command and the DLL, then creates the necessary database queries for exploitation.



## References
Preparing Visual Studio for compiling DLLs might be a little tricky, but you can check  these to help you: [Here](https://stackoverflow.com/questions/52642069/how-to-create-dll-project-in-vs2017-correctly), [Here](https://www.2ndquadrant.com/en/blog/compiling-postgresql-extensions-visual-studio-windows/), [Here](https://learn.microsoft.com/en-us/cpp/build/walkthrough-creating-and-using-a-dynamic-link-library-cpp?view=msvc-170#to-add-the-dll-import-library-to-your-project), [Here](https://learn.microsoft.com/en-us/visualstudio/sharepoint/how-to-add-a-resource-file?view=vs-2022), [Here](https://stackoverflow.com/questions/6769760/how-do-files-get-into-the-external-dependencies-in-visual-studio-c), and [Here](https://blog.conan.io/2021/02/10/Dependencies-Visual-Studio-C++-property-files.html).



The cmd.c file is an edit for the original script at [sourceincite](https://github.com/sourceincite/tools/blob/master/pgpwn.c).

The script.py file is an edit for the original script at [sourceincite](https://srcincite.io/blog/2020/06/26/sql-injection-double-uppercut-how-to-achieve-remote-code-execution-against-postgresql.html).
