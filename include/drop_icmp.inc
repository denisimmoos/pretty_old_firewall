#!/bin/bash
# FILE: drop_icmp.inc
# DESC: drop_icmp Rules
# DATE: 08.09.2006
# AUTOR: Denis Immoos

# SAVE IFS
OLDIFS=$IFS
IFS=","

for each in ${drop_icmp}
do
	#CHECK IP
	f_check_ip ${each}

	echo "DROP ICMP FOR (${each}) ON (${interface[$i]}) ... "

	# DROP ICMP INPUT
	${IPTABLES} -A INPUT -i ${interface[$i]} \
	-s ${each} \
	-d ${interface_ip[$i]}/${interface_subnet_mask[$i]} \
	-p icmp -j LDROP \
	|| f_error "drop_icmp"

done

# UNSET
unset each

# RESTORE IFS
IFS=$OLDIFS

#__END__
