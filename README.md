This repository provides a template for starting a new C project using Sig's build system! Updates are automatically propogated. Run `./sig` for a list of commands and then use follow the instructions given to invoke them. Adjust variables as necessary in the `sig` command file.

```
@sigonasr2 ➜ /workspaces/CProjectTemplate (main) $ ./sig
Dev build, no checks required.

  Usage: ./sig <command> {args}

====    Current Configuration   =====================
        PROJECT_NAME       CProjectTemplate
        BUILD_OPTIONS             -lncurses
        LANGUAGE                          C
=====================================================

  Command List:

        build          Compiles the entire program then runs it, producing an executable.
        commit         Adds a commit message and pushes project to github repository.  
'``