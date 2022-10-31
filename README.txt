
********************************************  SYSTEMS PROGRAMMING - HOMEWORK 2 & 3*********************************************************

## Source Code Working Explanation:

# program will support 4 different commands such as -S -s -f -t
# program will support 2 extra commands which are -E -e
    -S 
        this command fetches all the files and directories along with file_size, last access date, file permissions from the path specified 
        
        Example
                filename (size) (last access time) (permissions)

                # permissions:
                    drwxrwxrwx
                    d  -> directory / file
                    rwx -> read,write,execution -> owner
                    rwx -> read,write,execution -> group
                    rwx -> read,write,execution -> others



    -s <file_size_limit>
        this command fetches all the files with the file size less than or equal to value mentioned.


    -f <pattern> <depth>
        this command fetches all the files in file heirearchy where as file/directory name has pattern as substring
        it lists down the data upto the relative depth(heigh of tree from parent directory/folder) mentioned above

        Example 
                    ./search -f .c 0

                            hw1.c
                            hw2.c
                            hw3.c
                    ./search -f .c 1
                            hw1.c
                                    hw4.c
                            hw2.c
                                    hw5.c
                            hw3.c
    
    -t f
        fetches all regular files from the path mentioned.

    -t d
        fetches all directories from the path mentioned.

    -e "<command>
        fetches and executes every file one by one with unix command given
    -E <"command">
        fetched and executes all files and directories at a time with the unix command given

        Example 
                ./search -e "wc -l"
                ./search -E "wc -l"
                ./search -f .c 2 -e "wc -l"
                ./search -f .c 2 -E "wc -l"
                ./search -e "stat"
                ./search -E "stat"
                ./search -f .c 2 -e "stat"
                ./search -f .c 2 -E "stat"



## Code Compilation:

        gcc -o search search.c
        <or> 
        make -f MakeFile all

## Code Execution Commands:

    you can try combination of any commands mentioned above.
    
    pwd  <-- gets you the current path use this command for path usage

    ./search 

    ./search path/default

    ./search -S path/default

    ./search -s <SIZE> path/default

    ./search -t d path/default

    ./search -t f path/default

    ./search -f <pattern> <depth> path/default

    ./search -S -s <SIZE> path/default

    ./search -S -s <SIZE> -f <pattern> <depth> path/default

    ./search -S -s <SIZE> -t d path/default

    ./search -S -s <SIZE> -t f path/default

    ./search -S -s <SIZE> -f <pattern> <depth> -t d path/default

    ./search -S -s <SIZE> -f <pattern> <depth> -t f path/default

    ./search -e "<command>" path/default

    ./search -S -e <"command"> path/default

    ./search -s <SIZE> -e <"command"> path/default

    ./search -f <pattern> <depth> -e <"command"> path/default

    ./search -S -s <SIZE> -e "<command>" path/default

    ./search -S -s <SIZE> -f <pattern> <depth>  -e "<command>" path/default

    ./search -S -s <SIZE> -t d -e "<command>" path/default

    ./search -S -s <SIZE> -t f -e "<command>" path/default

    ./search -S -s <SIZE> -f <pattern> <depth> -t d -e "<command>"  path/default

    ./search -S -s <SIZE> -f <pattern> <depth> -t f -e "<command>" path/default

    ./search -E "<command>" path/default

    ./search -S -E <"command"> path/default

    ./search -s <SIZE> -E <"command"> path/default

    ./search -f <pattern> <depth> -E <"command"> path/default

    ./search -S -s <SIZE> -E "<command>" path/default

    ./search -S -s <SIZE> -f <pattern> <depth>  -E "<command>" path/default

    ./search -S -s <SIZE> -t d -E "<command>" path/default

    ./search -S -s <SIZE> -t f -E "<command>" path/default

    ./search -S -s <SIZE> -f <pattern> <depth> -t d -E "<command>"  path/default

    ./search -S -s <SIZE> -f <pattern> <depth> -t f -E "<command>" path/default

    


## Reference files from lab work:
    readdir.c, lstat.c, funcptr.c, readdir_v2.c in the lab 5 assignment, lab 7 assignment and sample codes.
    fork.c, forkexecvp2.c

##Reference from online:
    used for getting file permissions related functions
    https://www.gnu.org/software/libc/manual/html_node/Permission-Bits.html 
