#---------------------------------------------------------------------------------------------------------
# Name       : Milan Bui
# Date       : 11 Oct 2020
# Class      : CS 2600.01
# Script     : project1.bash
# Assignment : Project 1
# Description:
#    Collects and stores Daily Show podcasts. 2 modes: 1st doesn't take parameters and maintains the 
#    directories, reading the latest RSS feed / 2nd takes and action as parameter (done or keep) > keep
#    moves podcast from new to keep directory and done moves podcast to old directory and empties content
#---------------------------------------------------------------------------------------------------------

# VARIABLES
URL='https://feeds.megaphone.fm/the-daily-show' # RSS feed for podcasts
FILE_PATH=/tmp/podcasts                         # Path to store RSS feed from wget
COUNT=1                                         # Counter to iterate through mp3 urls when downloading


# MODE 1 -------------------------------------------------------------------------------------------------

# If no parameters were given -> enter mode 1
if [[ "$1" == "" ]]; then
	
	# Gets RSS feed from URL and saves to the given file (/tmp/podcasts)
	wget -O $FILE_PATH -q $URL

	# Creates directories if not yet existing	
	if [[ ! -e ~/.podcastdb && ! -d ~/.podcastdb ]]; then
		mkdir -p ~/.podcastdb
	fi
	
	if [[ ! -e ~/.podcastdb/new && ! -d ~/.podcastdb/new ]]; then
		mkdir -p ~/.podcastdb/new
	fi

	if [[ ! -e ~/.podcastdb/keep && ! -d ~/.podcastdb/keep ]]; then
		mkdir -p ~/.podcastdb/keep
	fi
	
	if [[ ! -e ~/.podcastdb/old && ! -d ~/.podcastdb/old ]]; then
		mkdir -p ~/.podcastdb/old
	fi

	# Downloads podcasts (loops until it count excedes # of files to download)
	until [[ $COUNT -gt $(grep -c "<enclosure url=" $FILE_PATH) ]]; do
		
		# MP3_URL = url for podcast file / FILE = the unique part of the URL to be the file name
		MP3_URL=$(grep "<enclosure url=" $FILE_PATH | cut -d '"' -f2 | head -n $COUNT | tail -n 1)
		FILE=$(echo $MP3_URL | cut -d '/' -f10 | cut -d '?' -f1)

		echo -n "Found $FILE..."
 
		# Checks if podcast is already in new, old, or keep; otherwise, it downloads it
		if [[ -e ~/.podcastdb/new/"$FILE" ]]; then
			echo "already in new."

		elif [[ -e ~/.podcastdb/old/"$FILE" ]]; then
			echo "already in old."
	
		elif [[ -e ~/.podcastdb/keep/"$FILE" ]]; then
			echo "already in keep."
		
		else
			echo -n "downloading..."
		 	wget -O ~/.podcastdb/new/"$FILE" -q $MP3_URL
			echo "done."	
		fi

		# Increments counter
		COUNT=$(( $COUNT + 1 ))
	 
	done

# MODE 2 -------------------------------------------------------------------------------------------------	

# If 1st parameter given is keep -> enter mode 2 for "keep" action
elif [[ "$1" == "keep" ]]; then
	
	# If no file name was given
	if [[ "$2" == "" ]]; then
		echo "Error: file not specified"

	# Else, if the file exists in the new directory
	elif [[ -e ~/.podcastdb/new/"$2" ]]; then

		# If the file is also in the keep directory
		if [[ -e ~/.podcastdb/keep/"$2" ]]; then

			echo "Error: $2 already exists in ~/.podcastdb/keep"

			# Displays md5 hash for the two files (to see if same or different)
			md5sum ~/.podcastdb/new/"$2"
			md5sum ~/.podcastdb/keep/"$2" 

		# Else (in new directory and not in keep directory), move to keep
		else
			mv ~/.podcastdb/new/"$2" ~/.podcastdb/keep
		fi

	# Else (file name given but is not in new)
	else
		echo "Error: $2 does not exit in ~/.podcastdb/new"
	fi

# If 1st parameter given is done -> enter mode 2 for "done" action
elif [[ "$1" == "done" ]]; then

	# If no file name is given
	if [[ "$2" == "" ]]; then
		echo "Error: file not specified"

	# Else, if the file exists in the new directory
	elif [[ -e ~/.podcastdb/new/"$2" ]]; then

		# Remove from new directory and creates new, empty file in old directory
		# To "move" file to old and empty contents
		rm ~/.podcastdb/new/"$2"
		touch ~/.podcastdb/old/"$2"

	# Else (file name is given but no in new directory)
	else
		echo "Error: $2 does not exist in ~/.podcastdb/new"
	fi

# If 1st parameter is given but not "keep" or "done" -> unrecognized
else

	echo "Error: Action '$1' unknown"

fi