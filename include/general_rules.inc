#!/bin/bash
# FILE: general.inc
# DESC: General Rules
# DATE: 08.09.2006
# AUTOR: Denis Immoos

echo "GENERAL INPUT RULES ... "

# DROP INVALID packets (not ESTABLISHED, RELATED or NEW)
${IPTABLES} -A INPUT -m state --state INVALID -j LINVALID

# Check TCP-Packets for Bad Flags
${IPTABLES} -A INPUT -p tcp -j CHECKBADFLAG

# DROP and LOG UDP-Traceroute
${IPTABLES} -A INPUT -m state --state NEW \
-p udp --dport $TRACEROUTEPORTS -j LDROP

# GENERAL OUTPUT RULES

echo "GENERAL OUTPUT RULES ... "

# DROP INVALID packets (not ESTABLISHED, RELATED or NEW)
${IPTABLES} -A OUTPUT -m state --state INVALID -j LINVALID

# Check TCP-Packets for Bad Flags 
${IPTABLES} -A OUTPUT -p tcp -j CHECKBADFLAG

# Set TOS values
${IPTABLES} -t mangle -A OUTPUT -j MANGLEOUTPUT

# DROP UDP-Traceroute
${IPTABLES} -A OUTPUT -m state --state NEW \
-p udp --sport $TRACEROUTEPORTS -j LDROP

# GENERAL FORWARD RULES

echo "GENERAL FORWARD RULES ... "

# Kill invalid packets (not ESTABLISHED, RELATED or NEW)
${IPTABLES} -A FORWARD -m state --state INVALID -j LINVALID

# Check TCP-Packets for Bad Flags 
${IPTABLES} -A FORWARD -p tcp -j CHECKBADFLAG

# Block UDP-Traceroute
${IPTABLES} -A FORWARD -m state --state NEW \
-p udp --dport ${TRACEROUTEPORTS} -j LDROP

#__END__
