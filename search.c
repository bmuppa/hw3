#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>


/* 
    Macros helpful for changes in future
*/
#define max_value 1001
#define emptystring sprintf(file_name,"%s", "");
#define copy(a,b) strcpy(a,b);
#define tabspace printf(" \t ");


long long int limit_value;
int depth_value;
int height_Check;
int file_counter = 0;
int commands[6] ={0,0,0,0,0,0};
char command_line_arguments[11] = "Ss:f:t:e:E";
char substring_pattern[max_value];
char file_type[max_value];
char file_name[max_value];
char e_name[max_value];
char E_name[max_value];
char E_list[max_value][max_value];
char permissions_array[10];


/*
    Function declarations
*/

typedef void Func_Pointer(struct stat lstat_buffer, int cnt, char *current_file_path, char *full_file_path);
void file_permissions(struct stat buffer);
void print_list(char *file_name, int level_cnt, char *full_file_path);
void get_files(char *folder_path, int level_cnt, Func_Pointer *func_pointer);
void get_argument_values(char argument);
int get_depth_value(int a, char **b);
void get_unix_commands(int a, char **b);
void run_unix_command_e();
void run_unix_command_E();
void tokenizer();
/*
        Author Name: Bhavana Muppa
        BlazerId: bmuppa
        Project #: implementing search command using C system calls (HomeWork 2)
        To compile: gcc -o search search.c or make -f MakeFile
        To run: ./search -S
                ./search -s 1024
                ./search -f .c 0
                ./search -t d
                ./search -t 
                please refer README.txt file for compilation and more execution commands in detail
*/

/*
    Referenced from lab codes  to execute a file as child process under the main parent process
    forkexecvp2.c as reference code
*/

void run_child_process(char *dummy[max_value]){
                                                                                                                                                                                                                                                                                                                                                                                                                                                
    pid_t child_run_id;
    child_run_id = fork();  
    int child_run_status;
    
    if (child_run_id == 0) 
    {
        execvp(dummy[0], dummy);
        perror("run error");
        exit(-1);
    } 
    else if (child_run_id > 0)
    {
        wait(&child_run_status);
	    if (WIFEXITED(child_run_status)==0)
	        printf("Child run incorrectly exited\n");
	} 
    else 
    {
		perror("fork issue"); 
		exit(EXIT_FAILURE);
	}
}

/*
    File structure print formatting function
    Checks -f command depth as well and prints files less than the depth given
*/

void print_list(char *file_name, int level_cnt, char *full_file_path){
    if (strcmp(file_name, "") != 0 && commands[4]==0)
    {
        for (int iterator =0;iterator<level_cnt+1;iterator++ ) {
            if(commands[2]==0)
                tabspace
        }
        if(commands[2]==1 && level_cnt<=height_Check){
            for (int j = 0;j<level_cnt+1;j++ ) {
                tabspace
            }
            if(commands[5]==1)
            {
                strcpy(E_list[file_counter+1],full_file_path);
            }
            if(commands[0]== 1){
                printf("%s %s\n",file_name,permissions_array);
            }
            else {
                printf("%s \n", file_name);
            }
        }
        else if(commands[2]==0){
            if(commands[0]== 1){
                printf("%s %s\n",file_name,permissions_array);
            }
            else   { 
                printf("%s \n", file_name);
            }
        }
    }
}

/*
    Checks file and directory permissions using lstat.st_mode 
    Does and operation with bits of lstat.st_mode and its binary value
    if value equals one permission available else not available

    Referenced from https://www.gnu.org/software/libc/manual/html_node/Permission-Bits.html 

*/
void file_permissions(struct stat buffer){
    permissions_array[0] = *( (S_ISDIR(buffer.st_mode)) ? "d" : "-");
    permissions_array[1] = *( (buffer.st_mode & S_IRUSR) ? "r" : "-");
    permissions_array[2] = *( (buffer.st_mode & S_IWUSR) ? "w" : "-");
    permissions_array[3] = *( (buffer.st_mode & S_IXUSR) ? "x" : "-");
    permissions_array[4] = *( (buffer.st_mode & S_IRGRP) ? "r" : "-");
    permissions_array[5] = *( (buffer.st_mode & S_IWGRP) ? "w" : "-");
    permissions_array[6] = *( (buffer.st_mode & S_IXGRP) ? "x" : "-");
    permissions_array[7] = *( (buffer.st_mode & S_IROTH) ? "r" : "-");
    permissions_array[8] = *( (buffer.st_mode & S_IWOTH) ? "w" : "-");
    permissions_array[9] = *( (buffer.st_mode & S_IXOTH) ? "x" : "-");
    if (S_ISREG(buffer.st_mode))
        permissions_array[0] ='f';
}

/*
    Function for filtering the files and directories according to command line arguments passed Ss:f:t:
    Added two new arguments , so updated argumentslists is as follows Ss:f:t:e:E
*/
void  commands_function(struct stat lstat_buffer,int level_cnt, char *current_file_path, char *full_file_path)
{
    emptystring
    strcat(file_name, current_file_path);
    if (commands[0] == 1)
    {
        char temporary_array[max_value];
        copy(temporary_array, " ");
        sprintf(temporary_array, "%lld", lstat_buffer.st_size);
        strcat(file_name, "  (");
        strcat(file_name, temporary_array);
        strcat(file_name, ")  ");
        char *time_val = ctime(&lstat_buffer.st_atime);
        time_val[strlen(time_val)-1]='\0';
        strcat(file_name,time_val);
        file_permissions(lstat_buffer);
    }

    if (((commands[3]==1) &&(S_ISDIR(lstat_buffer.st_mode) != 0) && (strcmp(file_type, "f") == 0)) ||((commands[3]==1) && (S_ISREG(lstat_buffer.st_mode) != 0) && (strcmp(file_type, "d") == 0 ))) {
        copy(file_name, "");
    }
    else if (commands[1] == 1 && lstat_buffer.st_size >= limit_value)
    {
        copy(file_name, "");
    }
    else if ( ((commands[2] == 1 && strstr(current_file_path, substring_pattern) == NULL))) {
        copy(file_name, "");
    }
    print_list(file_name, level_cnt, full_file_path);
    if (strcmp(file_name,"")!=0){
        if(commands[5]==1 && commands[3] == 0){
            if (strcmp(current_file_path,"")!=0  ){
                strcpy(E_list[file_counter++],full_file_path);
            }
        }
    if(commands[4]==1 && commands[3]==0 ){
        if (commands[5]==0)
            {
                if (strcmp(file_name,"")!=0 &&(S_ISDIR(lstat_buffer.st_mode)==0))
                {
                char *E_full_file_path[max_value];
                int cnt = 0;
                char *tkn = strtok(e_name, " ");
                while(tkn != NULL) {
                    E_full_file_path[cnt] = tkn;cnt = cnt + 1;tkn = strtok(NULL, " ");
                }
                E_full_file_path[cnt+1] = NULL;E_full_file_path[cnt] = full_file_path;
                run_child_process(E_full_file_path);
                }
            }
        }
    }
    
}

/*
    Recursively calls itself till it reaches down the end of file structure tree 
    calls a function pointer internally and prints them
*/

void get_files(char *folder_path, int level_cnt, Func_Pointer *func_pointer)
{
    struct dirent *dirent;
    DIR *directory_path = opendir(folder_path);
    if (!directory_path || (commands[2]==1 && depth_value == -1))
    {
        return;
    }
    while ((dirent = readdir(directory_path)) != NULL)
    {
        if (strcmp(dirent->d_name,".") && strcmp(dirent->d_name,".."))
        {
            char full_file_path[max_value] ;
            copy(full_file_path, folder_path);
            strcat(full_file_path, "/");
        	strcat(full_file_path, (*dirent).d_name);
            struct stat lstat_buffer;
            lstat(full_file_path, &lstat_buffer);
            func_pointer(lstat_buffer,level_cnt, (*dirent).d_name,full_file_path);
            if ((*dirent).d_type == DT_DIR)
            {
                level_cnt = level_cnt + 1;get_files(full_file_path,level_cnt, func_pointer);
                level_cnt = level_cnt - 1;
            }
        }
    }
    closedir(directory_path);
}

/*
    Extracting command line args and setting up command bits as true for later usage
*/

void get_argument_values(char argument) {

    if(argument == 'S')
        commands[0] = 1;
    if(argument == 's')
        {commands[1] = 1; limit_value = atoi(optarg);}
    if(argument == 'f')
        {commands[2] = 1;    copy(substring_pattern,optarg);  }
    if(argument == 't')
        {commands[3] = 1; }
    // if(argument == 'e')
    //     {commands[4] = 1;}
    // if(argument == 'E')
    //     {
    //         commands[5] = 1; 
    //         tokenizer();
    //     }
}

/*
    Added new code
    Tokenize the string and copy it.
*/

void tokenizer(){
    char *tokeniser = strtok(E_name," ");   
    while( tokeniser != NULL ) {
        copy(E_list[file_counter++], tokeniser); 
        tokeniser = strtok(NULL, " ");
    }  
}
/*
    Extracting depth value and file_type from command line arg -f  and arg -t when they are specified

*/
int get_depth_value(int a, char **b){

    int iterator = 0;
    char *height;
    int output;
    while(iterator<a){
        if(strcasecmp(b[iterator],"-f")==0){
            height = b[iterator+2];
            output = atoi(height);
        }
        if(strcmp(b[iterator],"-t")==0){
            commands[3] = 1;
            strcpy(file_type,b[iterator+1]);
        }
        iterator = iterator + 1;
    }
    return output;
}

/*
    Addded new code
    To fetch unix commands, as we have three arguments for f, we need to get optional arguments this way , as we have dont another option to fetch unixcommands when -f is given
*/

void get_unix_commands(int a, char **b){
    int iterator = 0;
    while(iterator<a){
        if(!strcmp(b[iterator],"-e")){
            commands[4] = 1;
            copy(e_name,b[iterator+1]);
        }
        if(!strcmp(b[iterator],"-E")){
            commands[5] = 1;
            copy(E_name,b[iterator+1]);
            tokenizer();
        }
        iterator = iterator + 1;
    }
}

/*
    Added new code
    Run the unix_commands on top of the given filepath.
*/

void run_unix_command_E(){
    int count = 0; 
    char *E_full_file_path[max_value]; 
    if (commands[5]){
        
        while(count<file_counter){
            E_full_file_path[count] = E_list[count];count = count + 1;
        }
        E_full_file_path[count] = NULL;
        run_child_process(E_full_file_path);
        }
    }

int main(int argc, char **argv)
{
    int opt = 0;
    char folder_path[max_value];
    copy(folder_path,argv[argc-1]);
    get_unix_commands(argc,argv);

    while ((opt = getopt(argc, argv, command_line_arguments)) != EOF)
    {
       char argument = opt;
       get_argument_values(argument);
    }

    depth_value = get_depth_value(argc,argv);
    height_Check = depth_value;
    

    if(opendir(folder_path)){
        char  *user_path = argv[argc -  1];
        get_files(user_path,0,commands_function); 
        
    }
    else{
        getcwd(folder_path, max_value);
        get_files(folder_path,0,commands_function);
    }  
    run_unix_command_E();
    return 0;
}