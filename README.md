# Viruses
Collection of custom made viruses

# Purpose
Test different types of viruses in controlled and monitored enviroments to promote ethical hacking.

# Self replicating Virus
Corrupt_files.c + Corrupt_fileV2.c

- Uses command line arguments in order to test in a controlled setting
  - Use test folder
- Copies data from every file into new directory doc
- Prints itself in infected files
  - Waits for files to be run in order to continue spreading
- Working on new version which will use C's fork calls in order to create more processes running the virus
 
# Jammer
Jammer.c

- Simple yet effective virus that uses C's system function in order to create an infinitely growing funciton
- Program is safegaurded by exit statements and quotes in system call
 - Will not run as intended without removing the following:
   printf("DO NOT RUN!\nExiting...\n");
    exit(0);
   
   * And replacing the following *
     system(“dir>>â.ša.exe”);
     with
     system(dir>>â.ša.exe);
     
- Do NOT run with the above changes
- Run at your own risk

Hoping to add more viruses in the future
