#---------------------------------------------------------------------------------------------------------
# Name       : Milan Bui
# Date       : 2020.09.17
# Class      : CS 2600.01 | Gershman
# File       : homework2.bash
# Assignment : Homework 2
# Description: Generates a report for a directory tree complete with a header and specified date format,
#              all saved to a file (name given by user once prompted)
#---------------------------------------------------------------------------------------------------------

# VARIABLES
FILE_PATH=/home/student/homework2                           # Path to directory where file will be created
DIRECTORY=/home                                             # Directory to be tree'd


read -p 'Please enter the output file name: ' FILE_NAME     # Prompts user for file name

cd $FILE_PATH                                               # Changes directories to PATH
                                                 
                                                            # Below > creates file if it doesnt exist 
echo '------------------------------------------------------------------------------' > $FILE_NAME 
echo 'Name      : Milan Bui' >> $FILE_NAME                  # Outputs name to file
echo 'Class     : CS 2600.01' >> $FILE_NAME                 # Outputs class to file
echo 'Assignment: Homework 2' >> $FILE_NAME                 # Outputs assignment name to file 
date +'Generated : %d %B %Y @ %I:%M%p' >> $FILE_NAME        # Outputs date of generation in file
echo 'Directory to be treed:' "$DIRECTORY" >> $FILE_NAME    # Outputs directory to be treed to file
echo -e '------------------------------------------------------------------------------\n' >> $FILE_NAME

cd $DIRECTORY                                               # Changed directories to DIRECTORY 
tree $DIRECTORY >> $FILE_PATH/$FILE_NAME                    # Outputs directory tree to file  
