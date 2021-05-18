// Read the binary Department Directory file 'cse_dpts.dat' to locate
// a given email address and print the Department / Name of the person
// associated with it. See 'print_department.c' for the structure of
// the binary file.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>

// type for individual contact
typedef struct {
  char name[128];      // name of contact person
  char email[128];     // email address 
} contact_t;

// type indicating position and size of array of contacts in the file
typedef struct {
  char dept_code[16];  // short identifier code for department
  size_t offset;       // byte offset in file where contact_t array starts
  int num_contacts;    // number of contact_t's for this department
} dept_offset_t;

// type indicating initial identifying and size information
typedef struct {
  unsigned char ident[4]; // identifying bytes should be {0xDE,'D','I','R'}
  int num_depts;          // number of departments in dept_offset_t array
} file_header_t;

int main(int argc, char *argv[]){
  if(argc < 3){
    printf("usage: %s <file.dat> <email>\n",argv[0]);
    printf("  <email> is an email address to look up and print out\n");
    return 1;
  }
  char *filename  = argv[1];
  char *email     = argv[2];

  // memory map the binary data file
  int fd = open(filename, O_RDONLY);         // call open on file to get file descriptor

  struct stat stat_buf;                      // call fstat() to get stats on the open file such as size
  fstat(fd, &stat_buf);

  int size = stat_buf.st_size;               // size for mmap()'ed memory is size of file

  char *file_bytes =                         //  call mmap() to create a pointer pointer to file contents
    mmap(NULL, size, PROT_READ, MAP_SHARED,
         fd, 0);

  file_header_t *header =                    // assign to point at header struct at the beginning of the file
    (file_header_t *) file_bytes;

  // CHECK the file_header_t struct for integrity, size of department array
  int ident_matches =                        // check the first bytes to ensure correct file format
    header->ident[0] == 0xDE &&
    header->ident[1] == 'D'  &&
    header->ident[2] == 'I'  &&
    header->ident[3] == 'R';

  if(!ident_matches){
    printf("'%s' does not appear to be a binary department directory file\n",
           filename);
    exit(1);
  }

  // SEARCH each department for specified email; print if found and
  // break from nested loops.

  dept_offset_t *depts_arr =                 // assign to the array of departmenets immediately after the header
    (dept_offset_t *) (file_bytes + sizeof(file_header_t));

  int num_depts = header->num_depts;         // header was ok, retrieve the number of departments

  int found = 0;                             // indicates that email has been located in the loop

  for(int i=0; i<num_depts; i++){            // iterate over the array checking for desired department_code

    contact_t *contacts =                    // point at array of contacts for the ith department
      (contact_t *) (file_bytes + depts_arr[i].offset);

    for(int j=0; j<depts_arr[i].num_contacts; j++){ // iterate over the array of contacts in the department

      // use an if() w/ string comparison to check if the jth contact email matches the search email from the command line
      if(strcmp(email, contacts[j].email) == 0) {

        printf("Found %s: %s Department --> %s\n",
               email, depts_arr[i].dept_code, contacts[j].name);

        found = 1;                           // found - break out of inner loop
        break;
      }
    }

    if(found==1){                            // found - break from outer loop
      break;
    }
  }

  if(found == 0){
    printf("Email '%s' not found\n",email);
  }

  munmap(file_bytes, size);                  // unmap and close file
  close(fd);

  return 0;
}
