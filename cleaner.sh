#! /bin/sh

while [ $# -ne 0 ]
do
    case $1 in
    -d )
        shift
        DIRECTORY=$1
        ;;   
    -p )
        shift
        PATTERN=$1          
        ;;
    -e )
        OPERATION="EXCLUDE"   
        ;;   
    -E )
        OPERATION="DELETE"
        ;;
    -l )
        OPERATION="LIST"
        ;;
    esac 
    shift
done

PATTERN=`echo ${PATTERN} | tr "," "|"`

SOURCE=`find "${DIRECTORY}" -type f | egrep "\.(${PATTERN})$"`

if [ "${OPERATION}" = "LIST" ]
then
   echo "${SOURCE}" 
else 
    find "${DIRECTORY}" ! -path "*/\.*" |
    while read FILE 
    do
        ! echo "${SOURCE}" | egrep "^${FILE}/|^${FILE}$" > /dev/null && {
            if [ "${OPERATION}" = "EXCLUDE" ]
            then
                echo "${FILE}"
            elif [ "${OPERATION}" = "DELETE" ]
            then
                rm -r "${FILE}" 2> /dev/null
            fi
        }
    done
fi
