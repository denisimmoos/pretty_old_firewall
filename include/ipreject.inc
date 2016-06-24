#!/bin/bash
# FILE: ipreject.inc
# DESC: IPREJECT Log Rule
# DATE: 12.09.2006
# AUTOR: Denis Immoos

if [ "${IPREJECT}" != "0" ];then

	
	# INCLUDE IPREJECT CHAIN
	f_include ${FW_INCLUDE_DIR}/ipreject_chain.inc

	# Catch all rule INPUT
	${IPTABLES} -A INPUT -j IPREJECT

	# Catch all rule OUTPUT
	${IPTABLES} -A OUTPUT -j IPREJECT

	# Catch all rule FORWARD
	${IPTABLES} -A FORWARD -j IPREJECT

fi

#__END__
