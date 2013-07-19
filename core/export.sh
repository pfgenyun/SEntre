#! /bin/sh

OUTPATH="../api/include/"

PRE="se_"
API_H="se_api.h"
MODE_H="se_mode.h"

if [ ! -f "${OUTPUT}${MODE_H}" ]
then touch "${OUTPATH}${MODE_H}"
fi

if [ ! -f "${OUTPUT}${API_H}" ]
then touch "${OUTPATH}${API_H}"
fi

if [ ! -d "$OUTPATH" ]
then mkdir "$OUTPATH"
fi

############################################## se_mode.h
echo "/************************************************************" >> ${OUTPATH}${MODE_H}
echo "* Copyright (c) 2013-present MeiWenBin.  All rights reserved." >> ${OUTPATH}${MODE_H}
echo "************************************************************/" >> ${OUTPATH}${MODE_H}
echo "" >> ${OUTPATH}${MODE_H}
echo "/*" >> ${OUTPATH}${MODE_H}
echo "* Redistribution and use in source and binary forms, with or without" >> ${OUTPATH}${MODE_H}
echo "* modification, are permitted provided that the following conditions are met:" >> ${OUTPATH}${MODE_H}
echo "*" >> ${OUTPATH}${MODE_H}
echo "* Redistribution and use in source and binary forms must authorized by" >> ${OUTPATH}${MODE_H}
echo "* Peng Fei." >> ${OUTPATH}${MODE_H}
echo "*" >> ${OUTPATH}${MODE_H}
echo "* Redistributions of source code must retain the above copyright notice," >> ${OUTPATH}${MODE_H}
echo "* this list of conditions and the following disclaimer." >> ${OUTPATH}${MODE_H}
echo "*" >> ${OUTPATH}${MODE_H}
echo "* Redistributions in binary form must reproduce the above copyright notice," >> ${OUTPATH}${MODE_H}
echo "* this list of conditions and the following disclaimer in the documentation" >> ${OUTPATH}${MODE_H}
echo "* and/or other materials provided with the distribution." >> ${OUTPATH}${MODE_H}
echo "*/" >> ${OUTPATH}${MODE_H}
echo "" >> ${OUTPATH}${MODE_H}

echo "#ifndef SE_MODE_H" >> ${OUTPATH}${MODE_H}
echo "#define SE_MODE_H" >> ${OUTPATH}${MODE_H}
echo "" >> ${OUTPATH}${MODE_H}

echo "#ifdef API_MODE" >> ${OUTPATH}${MODE_H}
echo "#ifdef TRACE" >> ${OUTPATH}${MODE_H}
echo "#define SEntre_mode entre_is_mem_instruction(insn)" >> ${OUTPATH}${MODE_H}
echo "#define SEntre_analysis entre_trace_record" >> ${OUTPATH}${MODE_H}
echo "#endif" >> ${OUTPATH}${MODE_H}
echo "" >> ${OUTPATH}${MODE_H}
echo "#ifdef BB_FREQ" >> ${OUTPATH}${MODE_H}
echo "#define SEntre_mode entre_is_bb_begin(addr_end)" >> ${OUTPATH}${MODE_H}
echo "#define SEntre_analysis entre_bb_freq_record" >> ${OUTPATH}${MODE_H}
echo "#endif" >> ${OUTPATH}${MODE_H}
echo "#endif" >> ${OUTPATH}${MODE_H}
echo "" >> ${OUTPATH}${MODE_H}
echo "#endif" >> ${OUTPATH}${MODE_H}

############################################## se_api.h
echo "/************************************************************" >> ${OUTPATH}${API_H}
echo "* Copyright (c) 2013-present MeiWenBin.  All rights reserved." >> ${OUTPATH}${API_H}
echo "************************************************************/" >> ${OUTPATH}${API_H}
echo "" >> ${OUTPATH}${API_H}
echo "/*" >> ${OUTPATH}${API_H}
echo "* Redistribution and use in source and binary forms, with or without" >> ${OUTPATH}${API_H}
echo "* modification, are permitted provided that the following conditions are met:" >> ${OUTPATH}${API_H}
echo "*" >> ${OUTPATH}${API_H}
echo "* Redistribution and use in source and binary forms must authorized by" >> ${OUTPATH}${API_H}
echo "* Peng Fei." >> ${OUTPATH}${API_H}
echo "*" >> ${OUTPATH}${API_H}
echo "* Redistributions of source code must retain the above copyright notice," >> ${OUTPATH}${API_H}
echo "* this list of conditions and the following disclaimer." >> ${OUTPATH}${API_H}
echo "*" >> ${OUTPATH}${API_H}
echo "* Redistributions in binary form must reproduce the above copyright notice," >> ${OUTPATH}${API_H}
echo "* this list of conditions and the following disclaimer in the documentation" >> ${OUTPATH}${API_H}
echo "* and/or other materials provided with the distribution." >> ${OUTPATH}${API_H}
echo "*/" >> ${OUTPATH}${API_H}
echo "" >> ${OUTPATH}${API_H}

echo "#ifndef SE_API_H" >> ${OUTPATH}${API_H}
echo "#define SE_API_H" >> ${OUTPATH}${API_H}
echo "" >> ${OUTPATH}${API_H}
echo "#include \"se_mode.h\"" >> ${OUTPATH}${API_H}
echo "" >> ${OUTPATH}${API_H}

for i in `ls -R *.h`
do
	I=`echo $i | sed 's/\./\_/g' | tr [a-z] [A-Z]`
	tag=0
	tag_h=0
	while read LINE
	do
		echo "$LINE" | egrep "SEntre_api_end" > /dev/null
		if [ $? -eq 0 ]
			then tag=0
		fi
		if [ $tag -eq 1 ]
			then if [ $tag_h -eq 0 ]
			then echo "#include \"se_$i\"" >> ${OUTPATH}${API_H}
			echo "" >> ${OUTPATH}${API_H}
			tag_h=1
			fi
			echo "$LINE" | egrep "$I" > /dev/null
			if [ $? -eq 0 ]
				then echo "$LINE" | sed "s/$I/SE_$I/g" >> ${OUTPATH}${PRE}${i}
			else
				echo "$LINE" >> ${OUTPATH}${PRE}${i}
			fi
		fi
		echo "$LINE" | egrep "SEntre_api_begin" > /dev/null
		if [ $? -eq 0 ]
			then tag=1
		fi
	done < $i
done

echo "#endif" >> ${OUTPATH}${API_H}
