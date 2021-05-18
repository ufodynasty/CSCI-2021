/* Create a binary file which has the following structure.

   file_header_t struct
   - identifying bytes
   - size of following array of dept_offset_t array
   array of dept_offset_t structs
   - dept_code, offset, and num_contacts
   - length of this array is given in initial file_header_t
   - contains field offset which is bytes at which contacts for an
     associated department start
   array of contact_t structs
   - name and email fields
   - array is arranged by department
   - array of dept_offset_t structs indicate where each department starts
     and how many contacts are in it

   A verbose plain text example of this would be something along the
   following. Note that offsets are given by line while in the binary
   file they are given by byte offset.

   1. DEDIR 3 departments
   2. CS, starts at line 5, 8 contacts
   3. EE, starts at line 13, 6 contacts
   4. IT, starts at line 19, 5 contacts
   5. Arindam Banerjee, baner029@umn.edu
   6. Daniel Boley, boley@umn.edu
   7. Abhishek Chandra, chandra@umn.edu
   8. David Hung-Chang Du, du@umn.edu
   9. Maria Gini, gini@umn.edu
   10. Stephen Guy, sjguy@umn.edu
   11. Tian He, tianhe@umn.edu
   12. Mats Heimdahl, heimdahl@umn.edu
   13. Mehmet Akcakaya, akcakaya@umn.edu
   14. Massoud Amin, amin@umn.edu
   15. Raj Aravalli, aravalli@umn.edu
   16. Kia Bazargan, kia@umn.edu
   17. Itshak Bergel, ibergel@umn.edu
   18. Stephen Campbell, scampbell@umn.edu
   19. Joseph Axberg, jaxberg@umn.edu
   20. Carl Follstad, follstad@umn.edu
   21. Valarie Griep, griep003@umn.edu
   22. Richard Howey, howe0156@umn.edu
   23. Scott Kerlin, kerli012@umn.edu
*/
#include <stdio.h>

typedef struct {
  char name[128];      // name of contact person
  char email[128];     // email address 
} contact_t;

typedef struct {
  char dept_code[16];  // short identifier code for department
  size_t offset;       // byte offset in file where contact_t array starts
  int num_contacts;    // number of contact_t's for this department
} dept_offset_t;

typedef struct {
  unsigned char ident[4]; // identifying bytes should be {0xDE,'D','I','R'}
  int num_depts;          // number of departments in dept_offset_t array
} file_header_t;

contact_t cs_dept[] = {
  {"Arindam Banerjee", "baner029@umn.edu"},
  {"Daniel Boley","boley@umn.edu"},
  {"Abhishek Chandra","chandra@umn.edu"},
  {"David Hung-Chang Du","du@umn.edu"},
  {"Maria Gini","gini@umn.edu"},
  {"Stephen Guy","sjguy@umn.edu"},
  {"Tian He","tianhe@umn.edu"},
  {"Mats Heimdahl","heimdahl@umn.edu"},
};
  
contact_t ee_dept[] = {
  {"Mehmet Akcakaya","akcakaya@umn.edu"},
  {"Massoud Amin","amin@umn.edu"},
  {"Raj Aravalli","aravalli@umn.edu"},
  {"Kia Bazargan","kia@umn.edu"},
  {"Itshak Bergel","ibergel@umn.edu"},
  {"Stephen Campbell","scampbell@umn.edu"},
};
  
contact_t it_dept[] = {
  {"Joseph Axberg","jaxberg@umn.edu"},
  {"Carl Follstad","follstad@umn.edu"},
  {"Valarie Griep", "griep003@umn.edu"},
  {"Richard Howey", "howe0156@umn.edu"},
  {"Scott Kerlin", "kerli012@umn.edu"},
};


dept_offset_t offsets[] = {
  {"CS",-1,sizeof(cs_dept)/sizeof(contact_t)},
  {"EE",-1,sizeof(ee_dept)/sizeof(contact_t)},
  {"IT",-1,sizeof(it_dept)/sizeof(contact_t)},
};

file_header_t file_header = {
  .ident={0xDE,'D','I','R'},
  .num_depts=3,
};

int main(int argc, char *argv[]){
  if(argc < 2){
    printf("usage: %s <file.dat>\n",argv[0]);
    return 1;
  }

  offsets[0].offset = sizeof(file_header)+sizeof(offsets);
  offsets[1].offset = offsets[0].offset + sizeof(cs_dept);
  offsets[2].offset = offsets[1].offset + sizeof(ee_dept);

  FILE *fh = fopen(argv[1],"w");
  
  fwrite(&file_header, sizeof(file_header), 1,fh);
  fwrite(&offsets, sizeof(offsets), 1,fh);
  fwrite(&cs_dept, sizeof(cs_dept), 1,fh);
  fwrite(&ee_dept, sizeof(ee_dept), 1,fh);
  fwrite(&it_dept, sizeof(it_dept), 1,fh);
  fclose(fh);
  return 0;
}
