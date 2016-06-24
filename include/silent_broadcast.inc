#!/bin/bash
# FILE: silent_broadcast.inc
# DESC: silent_broadcast Rules
#
# DATE: 08.09.2006
# AUTOR: Denis Immoos


if [ "${SILENTBCAST}" != "0" ];then
	
	${IPTABLES} -A SILENTBCAST -p tcp \
    	-d ${interface_broadcast[$i]} \
    	-j DROP \
	|| f_error "silent_broadcast:1"

	${IPTABLES} -A SILENTBCAST -p udp \
    	-d ${interface_broadcast[$i]} \
    	-j DROP \
	|| f_error "silent_broadcast:2"

fi

#__END__
