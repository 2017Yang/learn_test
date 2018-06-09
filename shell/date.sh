#########################################################################
# File Name: date.sh
# Created Time: 2018年04月24日 星期二 21时21分51秒
#########################################################################
#!/bin/bash
startTime=`date +%s`
endTime=`date +%s`
internal=`expr $endTime - $startTime`
echo $internal
internal=0
while [ $internal -lt 30 ]
do
	#to do it
	echo "i am a persion"
	sleep 1
	endTime=`date +%s`
	echo endtime is $endTime
	internal=`expr $endTime - $startTime`
	echo $internal
done


echo $CURTIME

