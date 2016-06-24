#!/bin/bash
# FILE: log_rules.inc
# DESC: Log Rules
# DATE: 12.09.2006
# AUTOR: Denis Immoos

if [ "${SILENTBCAST}" != "0" ];then

  echo "SILENTBCAST LOG RULES ... "

  # Catch all rule INPUT
  ${IPTABLES} -A INPUT -j SILENTBCAST

  # Catch all rule OUTPUT
  ${IPTABLES} -A OUTPUT -j SILENTBCAST

  # Catch all rule FORWARD
  ${IPTABLES} -A FORWARD -j SILENTBCAST

fi

if [ "${SILENTICMP}" != "0" ];then

  echo "SILENTICMP LOG RULES ... "

  # Catch all rule INPUT
  ${IPTABLES} -A INPUT -j SILENTICMP

  # Catch all rule OUTPUT
  ${IPTABLES} -A OUTPUT -j SILENTICMP

  # Catch all rule FORWARD
  ${IPTABLES} -A FORWARD -j SILENTICMP

fi


if [ "${SILENTREJECT}" != "0" ];then

  echo "SILENTREJECT LOG RULES ... "

  # Catch all rule INPUT
  ${IPTABLES} -A INPUT -j SILENTREJECT

  # Catch all rule OUTPUT
  ${IPTABLES} -A OUTPUT -j SILENTREJECT

  # Catch all rule FORWARD
  ${IPTABLES} -A FORWARD -j SILENTREJECT

fi

if [ "${SILENTDROP}" != "0" ];then

	echo "SILENTDROP LOG RULES ... "

	# Catch all rule INPUT
	${IPTABLES} -A INPUT -j SILENTDROP

  	# Catch all rule OUTPUT
  	${IPTABLES} -A OUTPUT -j SILENTDROP

	# Catch all rule FORWARD
	${IPTABLES} -A FORWARD -j SILENTDROP

fi

if [ "${SPECIALPORT}" != "0" ];then

	# SEPARATE LOGGING OF SPECIAL PORTS INPUT
	${IPTABLES} -A INPUT \
	-j SPECIALPORT

	# SEPARATE LOGGING OF SPECIAL PORTS OUTPUT
	${IPTABLES} -A OUTPUT \
	-j SPECIALPORT

	# SEPARATE LOGGING OF SPECIAL PORTS OUTPUT
	${IPTABLES} -A FORWARD \
	-j SPECIALPORT

fi

if [ "${LOGDROP}" != "0" ];then

		echo "LOGDROP RULES ... "

  		# Catch all rule INPUT
  		${IPTABLES} -A INPUT -j LDROP

  		# Catch all rule OUTPUT
  		${IPTABLES} -A OUTPUT -j LDROP

  		# Catch all rule FORWARD
  		${IPTABLES} -A FORWARD -j LDROP

fi

#__END__
