#------------------------------------------------------------------------------------------------------
# Name       : Milan Bui
# Class      : CS 2600.01 | Gershman
# Date       : 2020.10.01
# Assignment : Homework 3
# Script     : homework3.bash 
# Description: Display CVSS score and the description of given CVE ID from command line
#------------------------------------------------------------------------------------------------------

# Variables
URL='https://nvd.nist.gov/vuln/detail/'                         # URL of site with CVSS Scores
CVEID=$(echo $1 | sed 's/c/C/' | sed 's/v/V/' | sed 's/e/E/')   # The CVE ID (handles if lower case)


 
# Script (start in home/student/CS2600/homework3 directory)

wget -O "/tmp/$CVEID" -q "$URL$CVEID"                           # Obtains html of CVE ID page

# Searches for, obtains, and displays cvss score from html > if no score found, displays NA 
echo -e '\nCVSS Score:' $(grep "label label-" "/tmp/$CVEID" | cut -d '>' -f2 | cut -d '<' -f1 | head -n 1 | sed 's/class=\"label label-default\"/NA/')

# Searches for, obtains, and displays the description of the CVE ID from the html
echo -e $(grep "\"vuln-description\"" "/tmp/$CVEID" | cut -d '>' -f2 | cut -d '<' -f1) '\n'
