#!/bin/bash
# FILE: nat.inc
# DESC: nat Rules
# DATE: 08.09.2006
# AUTOR: Denis Immoos

if [ "${nat}" = "1" ];then

	echo -n "NAT RULES (${interface[$i]}) ... "

	${IPTABLES} -A POSTROUTING -t nat \
	-o ${interface[$i]} \
	-j MASQUERADE
		
fi

#__END__
