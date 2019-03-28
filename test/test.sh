#!/bin/sh
if [ -n $TERM ]
then
	# Ansi excape color sequences
	RED="\033[1;31m"
	GREEN="\033[0;32m"
	BGREEN="\033[1;32m"
	BLUE="\033[0;34m"
	YELLOW="\033[0;33m"
	PURPLE="\033[0;35m"
	CYAN="\033[0;36m"
	GREY="\033[0;37m"

	# When printed reset the color
	COLRESET="\033[0m"

	# Move the cursor at the begining of the line
	MOVELINE="\033[1A"
	# Erase current line
	CLEARLINE="\033[K"
fi

# check if a program is given as arg
if [ $1 ]
then
	NAME=$1
else
	NAME='../21sh'
fi

VALGRIND=true
TEST_SHELL='bash'

# List of all files in which test are stored
TEST_FILES=$(find cmd -name '*.cmd')

# Temporary files for storing results
TCSH_OUT="tcsh_out.tmp"
TCSH_ERR="tcsh_err.tmp"
FTSH_OUT="42sh_out.tmp"
FTSH_ERR="42sh_err.tmp"
FTSH_LOG="42sh_log.tmp"

# Options used for valgrind
LOG_OPT="--log-file=$FTSH_LOG --quiet --leak-check=full"
LOG_OPT=$LOG_OPT" --suppressions=./osxerr.supp"

# Test if the executable exist
if [ -f $NAME -a -x $NAME ]
then
	# if it does run once on valgrind to remove the error valgrind
	# give to freshly compiled program
	# "warning: no debug symbols in executable (-arch x86_64)"
	if [ $VALGRIND ]
	then
		echo 'exit' | valgrind $NAME > /dev/null 2> /dev/null
	fi
else
	# Check if it isn't a command, for comparing with other shells
	if ! type $NAME > /dev/null
	then
		echo ${RED}[ERR]${COLRESET}"	: $NAME does not exist"
		exit 1
	fi
fi

# Make programs that kill themself
make -C bin/ 1>/dev/null 2>/dev/null

# Loop over each $FILE in cmd
for FILE in $TEST_FILES
do
	# Get a more 'sexy' version of the $FILE's path
	# ex: cmd/test18.cmd become test18
	SHORTFILE=$(echo $FILE | sed -e 's/^cmd\///g' | sed -e 's/\.cmd$//g')
	echo ${YELLOW}[...]${COLRESET}"	: "${SHORTFILE}${MOVELINE}

	# Test what result the reference shell gives
	$TEST_SHELL <$FILE 1>$TCSH_OUT 2>$TCSH_ERR
	TCSH_RTN=$?

	# Test what our shell gives
	if [ $VALGRIND ]
	then
		valgrind $LOG_OPT $NAME <$FILE 1>$FTSH_OUT 2>$FTSH_ERR
		FTSH_RTN=$?
	else
		$NAME <$FILE 1>$FTSH_OUT 2>$FTSH_ERR
		FTSH_RTN=$?
	fi

	# If anything is diffrent
	if diff -q $TCSH_OUT $FTSH_OUT > /dev/null \
			&& diff -q $TCSH_ERR $FTSH_ERR > /dev/null \
			&& test $TCSH_RTN == $FTSH_RTN \
			&& test ! -s $FTSH_LOG
	then
		echo ${CLEARLINE}${GREEN}[OK]${COLRESET}"	: "${SHORTFILE}
	else
		echo ${CLEARLINE}${RED}[KO]${COLRESET}"	: "${SHORTFILE}

		cat $FILE | sed -e "s/^/    /g"

		printf ${GREY}
			diff $TCSH_OUT $FTSH_OUT | sed -e "s/^/    /g"
		printf ${PURPLE}
			diff $TCSH_ERR $FTSH_ERR | sed -e "s/^/    /g"
		printf ${CYAN}
			if [ $TCSH_RTN != $FTSH_RTN ]
			then
				echo $TEST_SHELL retuned $TCSH_RTN | sed -e "s/^/    /g"
				echo $NAME retured $FTSH_RTN | sed -e "s/^/    /g"
			fi
		printf ${BLUE}
			if [ -f $FTSH_LOG ]
			then
				cat $FTSH_LOG | sed -e "s/^/    /g"
			fi
		printf ${COLRESET}
	fi
done

# Clear files
rm -f $TCSH_OUT $TCSH_ERR $FTSH_LOG $FTSH_OUT $FTSH_ERR