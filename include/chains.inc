#!/bin/bash
# FILE: chains.inc
# DESC: Firewall Chains
#
# DATE: 08.09.2006
# AUTOR: Denis Immoos

# These are the logging-chains.
# They all have a certain limit
# of log-entries/sec to prevent log-flooding

# LINVALID

  # Invalid packets
  # (not ESTABLISHED,RELATED or NEW)

  ${IPTABLES} -N LINVALID

  ${IPTABLES} -A LINVALID -m limit \
  --limit ${LOGLIMIT} \
  --limit-burst ${LOGLIMITBURST} -j LOG \
  --log-prefix "fp=INVALID:1 a=DROP "

  ${IPTABLES} -A LINVALID -j DROP

# LBADFLAG

  # TCP-Packets with one ore more bad flags

  ${IPTABLES} -N LBADFLAG

  ${IPTABLES} -A LBADFLAG -m limit \
  --limit ${LOGLIMIT} \
  --limit-burst ${LOGLIMITBURST} -j LOG \
  --log-prefix "fp=BADFLAG:1 a=DROP "

  ${IPTABLES} -A LBADFLAG -j DROP

# LSPECIALPORT

  # Logging of connection attempts
  # on special ports
  # (Trojan portscans, special services, etc.)

  ${IPTABLES} -N LSPECIALPORT

  ${IPTABLES} -A LSPECIALPORT -m limit \
  --limit ${LOGLIMIT} \
  --limit-burst ${LOGLIMITBURST} -j LOG \
  --log-prefix "fp=SPECIALPORT:1 a=DROP "

  ${IPTABLES} -A LSPECIALPORT -j DROP
  
# LSYNFLOOD

  # Logging of possible TCP-SYN-Floods
  
  ${IPTABLES} -N LSYNFLOOD

  ${IPTABLES} -A LSYNFLOOD -m limit \
  --limit ${LOGLIMIT} \
  --limit-burst ${LOGLIMITBURST} -j LOG \
  --log-prefix "fp=SYNFLOOD:1 a=DROP "

  ${IPTABLES} -A LSYNFLOOD -j DROP
  
# LPINGFLOOD

  # Logging of possible Ping-Floods

  ${IPTABLES} -N LPINGFLOOD

  ${IPTABLES} -A LPINGFLOOD -m limit \
  --limit ${LOGLIMIT} \
  --limit-burst ${LOGLIMITBURST} -j LOG \
  --log-prefix "fp=PINGFLOOD:1 a=DROP "

  ${IPTABLES} -A LPINGFLOOD -j DROP

# LDROP

  ${IPTABLES} -N LDROP

  ${IPTABLES} -A LDROP -p tcp -m limit \
  --limit ${LOGLIMIT} \
  --limit-burst ${LOGLIMITBURST} -j LOG \
  --log-prefix "fp=TCP:1 a=DROP "

  ${IPTABLES} -A LDROP -p udp -m limit \
  --limit ${LOGLIMIT} \
  --limit-burst ${LOGLIMITBURST} -j LOG \
  --log-prefix "fp=UDP:2 a=DROP "

  ${IPTABLES} -A LDROP -p icmp -m limit \
  --limit ${LOGLIMIT} \
  --limit-burst ${LOGLIMITBURST} -j LOG \
  --log-prefix "fp=ICMP:3 a=DROP "

  ${IPTABLES} -A LDROP -f -m limit \
  --limit ${LOGLIMIT} \
  --limit-burst ${LOGLIMITBURST} -j LOG \
  --log-prefix "fp=FRAGMENT:4 a=DROP "

  ${IPTABLES} -A LDROP -j DROP

# LREJECT

  ${IPTABLES} -N LREJECT

  ${IPTABLES} -A LREJECT -p tcp -m limit \
  --limit ${LOGLIMIT} \
  --limit-burst ${LOGLIMITBURST} -j LOG \
  --log-prefix "fp=TCP:1 a=REJECT "

  ${IPTABLES} -A LREJECT -p udp -m limit \
  --limit ${LOGLIMIT} \
  --limit-burst ${LOGLIMITBURST} -j LOG \
  --log-prefix "fp=UDP:2 a=REJECT "

  ${IPTABLES} -A LREJECT \
  -p icmp -m limit \
  --limit ${LOGLIMIT} \
  --limit-burst ${LOGLIMITBURST} -j LOG \
  --log-prefix "fp=ICMP:3 a=REJECT "

  ${IPTABLES} -A LREJECT -f -m limit \
  --limit ${LOGLIMIT} \
  --limit-burst ${LOGLIMITBURST} -j LOG \
  --log-prefix "fp=FRAGMENT:4 a=REJECT "  

  ${IPTABLES} -A LREJECT -p tcp \
  -j REJECT --reject-with tcp-reset

  ${IPTABLES} -A LREJECT -p udp \
  -j REJECT --reject-with icmp-port-unreachable

  ${IPTABLES} -A LREJECT -j REJECT
  
# LSPOOF

  ${IPTABLES} -N LSPOOF

  ${IPTABLES} -A LSPOOF -p tcp -m limit \
  --limit ${LOGLIMIT} \
  --limit-burst ${LOGLIMITBURST} -j LOG \
  --log-prefix "fp=TCP:1 a=LSPOOF "

  ${IPTABLES} -A LSPOOF -p udp -m limit \
  --limit ${LOGLIMIT} \
  --limit-burst ${LOGLIMITBURST} -j LOG \
  --log-prefix "fp=UDP:2 a=LSPOOF "

  ${IPTABLES} -A LSPOOF \
  -p icmp -m limit \
  --limit ${LOGLIMIT} \
  --limit-burst ${LOGLIMITBURST} -j LOG \
  --log-prefix "fp=ICMP:3 a=LSPOOF "

  ${IPTABLES} -A LSPOOF -f -m limit \
  --limit ${LOGLIMIT} \
  --limit-burst ${LOGLIMITBURST} -j LOG \
  --log-prefix "fp=FRAGMENT:4 a=LSPOOF "  

  ${IPTABLES} -A LSPOOF -p tcp \
  -j REJECT --reject-with tcp-reset

  ${IPTABLES} -A LSPOOF -p udp \
  -j REJECT --reject-with icmp-port-unreachable

  ${IPTABLES} -A LSPOOF -j REJECT
  

# TCPACCEPT 
  
  # Check for SYN-Floods before letting TCP-Packets in
  
  ${IPTABLES} -N TCPACCEPT

  ${IPTABLES} -A TCPACCEPT -p tcp \
  --syn -m limit \
  --limit ${TCPSYNLIMIT} \
  --limit-burst ${TCPSYNLIMITBURST} -j ACCEPT

  ${IPTABLES} -A TCPACCEPT \
  -p tcp --syn -j LSYNFLOOD

  ${IPTABLES} -A TCPACCEPT \
  -p tcp ! --syn -j ACCEPT

# CHECKBADFLAG 
  
  # Kill any Inbound/Outbound 
  # TCP-Packets with impossible
  # flag-combinations 
  # (Some port-scanners use these,
  # eg. nmap Xmas,Null,etc.-scan)

  ${IPTABLES} -N CHECKBADFLAG

  ${IPTABLES} -A CHECKBADFLAG -p tcp \
  --tcp-flags ALL FIN,URG,PSH -j LBADFLAG

  ${IPTABLES} -A CHECKBADFLAG -p tcp \
  --tcp-flags ALL SYN,RST,ACK,FIN,URG -j LBADFLAG

  ${IPTABLES} -A CHECKBADFLAG -p tcp \
  --tcp-flags ALL ALL -j LBADFLAG

  ${IPTABLES} -A CHECKBADFLAG -p tcp \
  --tcp-flags ALL NONE -j LBADFLAG

  ${IPTABLES} -A CHECKBADFLAG -p tcp \
  --tcp-flags SYN,RST SYN,RST -j LBADFLAG

  ${IPTABLES} -A CHECKBADFLAG -p tcp \
  --tcp-flags FIN,RST FIN,RST -j LBADFLAG

  ${IPTABLES} -A CHECKBADFLAG -p tcp \
  --tcp-flags SYN,FIN SYN,FIN -j LBADFLAG

  ${IPTABLES} -A CHECKBADFLAG -p tcp \
  --tcp-flags ACK,FIN FIN -j LBADFLAG

  ${IPTABLES} -A CHECKBADFLAG -p tcp \
  --tcp-flags ACK,PSH PSH -j LBADFLAG

  ${IPTABLES} -A CHECKBADFLAG -p tcp \
  --tcp-flags ACK,URG URG -j LBADFLAG

# SILENTREJECT 

  # Inbound/Outbound SILENTDROPS/REJECTS
  # (Things we dont want in our Logs)

  ${IPTABLES} -N SILENTREJECT

  # Silently reject Ident
  # (Don't DROP ident,
  # because of possible delays when
  # establishing an outbound connection)

  ${IPTABLES} -A SILENTREJECT -p tcp --dport 113 \
  -j REJECT --reject-with tcp-reset

  ${IPTABLES} -A SILENTREJECT -p tcp --sport 113 \
  -j REJECT --reject-with tcp-reset

# SILENTDROP

  # SMB-Traffic

  ${IPTABLES} -N SILENTDROP

  ${IPTABLES} -A SILENTDROP -p tcp \
  --dport 137:139 -j DROP
  
  ${IPTABLES} -A SILENTDROP -p tcp \
  --dport 445 -j DROP

  ${IPTABLES} -A SILENTDROP -p udp \
  --dport 137:139 -j DROP

  ${IPTABLES} -A SILENTDROP -p udp \
  --dport 445 -j DROP
  
  ${IPTABLES} -A SILENTDROP -p tcp \
  --sport 137:139 -j DROP

  ${IPTABLES} -A SILENTDROP -p tcp \
  --sport 445 -j DROP

  ${IPTABLES} -A SILENTDROP -p udp \
  --sport 137:139 -j DROP

  ${IPTABLES} -A SILENTDROP -p udp \
  --sport 445 -j DROP

# SILENTBCAST

  # Don't log any Broadcast

  ${IPTABLES} -N SILENTBCAST

  ${IPTABLES} -A SILENTBCAST -p udp -d ${BROADCAST} -j DROP
  ${IPTABLES} -A SILENTBCAST -p tcp -d ${BROADCAST} -j DROP


# SILENTICMP

  ${IPTABLES} -N SILENTICMP
  ${IPTABLES} -A SILENTICMP -p icmp -j DROP


# SPECIALPORT

  # Inbound Special Ports
  
  ${IPTABLES} -N SPECIALPORT
  
  # TCP

  # Direct Connect: TCP 411
  ${IPTABLES} -A SPECIALPORT -p tcp \
  --dport 411 -j LSPECIALPORT

  # Direct Connect: TCP 412
  ${IPTABLES} -A SPECIALPORT -p tcp \
  --dport 412 -j LSPECIALPORT

  # Grokster: TCP 1214
  # KaZaA: TCP 1214
  # Morpheus: TCP 1214
  ${IPTABLES} -A SPECIALPORT -p tcp \
  --dport 1214 -j LSPECIALPORT

  # Subseven Scan: TCP 1234
  # Hotline: TCP 1234
  ${IPTABLES} -A SPECIALPORT -p tcp \
  --dport 1234 -j LSPECIALPORT

  # eDonkey: TCP 4662
  ${IPTABLES} -A SPECIALPORT -p tcp \
  --dport 4662 -j LSPECIALPORT

  # Aimster: TCP 5025
  ${IPTABLES} -A SPECIALPORT -p tcp \
  --dport 5025 -j LSPECIALPORT

  # Hotline: TCP 5498
  ${IPTABLES} -A SPECIALPORT -p tcp \
  --dport 5498 -j LSPECIALPORT

  # Hotline: TCP 5499
  ${IPTABLES} -A SPECIALPORT -p tcp \
  --dport 5499 -j LSPECIALPORT
  
  # Hotline: TCP 5500:5501
  ${IPTABLES} -A SPECIALPORT -p tcp \
  --dport 5500:5501 -j LSPECIALPORT

  # Xorg: TCP 6000:6063
    ${IPTABLES} -A SPECIALPORT -p tcp \
  --dport 6000:6063 -j LSPECIALPORT

  # Bearshare: TCP 6346
  # Shareaza: TCP 6346
  # Gnutella: TCP 6346
  # Xolox: TCP 6346
  # LimeWire: TCP 6346
  ${IPTABLES} -A SPECIALPORT -p tcp \
  --dport 6346 -j LSPECIALPORT

  # LimeWire: TCP 6347
  ${IPTABLES} -A SPECIALPORT -p tcp \
  --dport 6347 -j LSPECIALPORT

  # Deepthroat Scan: TCP 6670
  ${IPTABLES} -A SPECIALPORT -p  tcp \
  --dport 6670 -j LSPECIALPORT

  # Napster: TCP 6699
  # WinMX: TCP 6699
  # Napster: TCP 6699
  ${IPTABLES} -A SPECIALPORT -p tcp \
  --dport 6699 -j LSPECIALPORT

  # Subseven Scan: TCP 6711:6713 
  ${IPTABLES} -A SPECIALPORT -p tcp \
  --dport 6711:6713 -j LSPECIALPORT  

  # Netbus Scan: TCP 20034
  ${IPTABLES} -A SPECIALPORT -p tcp \
  --dport 20034 -j LSPECIALPORT
  
  # Subseven Scan: TCP 27374 
  ${IPTABLES} -A SPECIALPORT -p tcp \
  --dport 27374 -j LSPECIALPORT

  # Netbus Scan: TCP 12345:12346
  ${IPTABLES} -A SPECIALPORT -p tcp \
  --dport 12345:12346 -j LSPECIALPORT

  # UDP

  # Subseven Scan: UDP 1234 
  ${IPTABLES} -A SPECIALPORT -p udp \
  --dport 1243 -j LSPECIALPORT

  # WinMX: UDP 6257
  ${IPTABLES} -A SPECIALPORT -p udp \
  --dport 6257 -j LSPECIALPORT

  # Bearshare: UDP 6346
  # Shareaza: UDP 6346
  # Gnutella: UDP 6346
  # Xolox: UDP 6346
  # LimeWire: UDP 6346
  # Shareaza: UDP 6346
  ${IPTABLES} -A SPECIALPORT -p udp \
  --dport 6346 -j LSPECIALPORT

  # eDonkey: TCP 4661
  ${IPTABLES} -A SPECIALPORT -p udp \
  --dport 4661 -j LSPECIALPORT

  # eDonkey: UDP 4665
  ${IPTABLES} -A SPECIALPORT -p udp \
  --dport 4665 -j LSPECIALPORT
    
  # Subseven Scan: UDP 27374 
    ${IPTABLES} -A SPECIALPORT -p udp \
  --dport 27374 -j LSPECIALPORT

  # Hack'a'Tack 2000: UDP 28431
  ${IPTABLES} -A SPECIALPORT -p udp \
  --dport 28431 -j LSPECIALPORT

  # Back Orifice scan: UDP 31337:31338
  ${IPTABLES} -A SPECIALPORT -p udp \
  --dport 31337:31338 -j LSPECIALPORT
  
# ICMPINBOUND

  # Inbound ICMP/Traceroute
  
  ${IPTABLES} -N ICMPINBOUND
  
  # Ping Flood protection. 
  # Accept ${PINGLIMIT} echo-requests/sec,
  # rest will be logged/dropped

  ${IPTABLES} -A ICMPINBOUND -p icmp \
  --icmp-type echo-request -m limit \
  --limit ${PINGLIMIT} \
  --limit-burst ${PINGLIMITBURST} -j ACCEPT

  ${IPTABLES} -A ICMPINBOUND -p icmp \
  --icmp-type echo-request -j LPINGFLOOD

  # Block ICMP-Redirects 
  # (Should already be catched by
  # sysctl-options, if enabled)
  
  ${IPTABLES} -A ICMPINBOUND -p icmp \
  --icmp-type redirect -j LDROP

  # Block ICMP-Timestamp
  # (Should already be catched
  # by sysctl-options, if enabled)
  
  ${IPTABLES} -A ICMPINBOUND -p icmp \
  --icmp-type timestamp-request -j LDROP
  
  ${IPTABLES} -A ICMPINBOUND -p icmp \
  --icmp-type timestamp-reply -j LDROP

  # Block ICMP-address-mask
  # (can help to prevent OS-fingerprinting)
  
  ${IPTABLES} -A ICMPINBOUND -p icmp \
  --icmp-type address-mask-request -j LDROP
    
  ${IPTABLES} -A ICMPINBOUND -p icmp \
  --icmp-type address-mask-reply -j LDROP

    # Allow all other ICMP in
    ${IPTABLES} -A ICMPINBOUND -p icmp -j ACCEPT
  
# ICMPOUTBOUND

  # Outbound ICMP/Traceroute
  
  ${IPTABLES} -N ICMPOUTBOUND

  # Block ICMP-Redirects 
  # (Should already be catched
  # by sysctl-options, if enabled)

  ${IPTABLES} -A ICMPOUTBOUND -p icmp \
  --icmp-type redirect -j LDROP

  # Block ICMP-TTL-Expired
  # MS Traceroute
  # (MS uses ICMP instead of UDp for tracert)
  
  ${IPTABLES} -A ICMPOUTBOUND -p icmp \
  --icmp-type ttl-zero-during-transit \
  -j LDROP
  
  ${IPTABLES} -A ICMPOUTBOUND -p icmp \
  --icmp-type ttl-zero-during-reassembly \
  -j LDROP

  # Block ICMP-Parameter-Problem
  
  ${IPTABLES} -A ICMPOUTBOUND -p icmp \
  --icmp-type parameter-problem -j LDROP

  # Block ICMP-Timestamp 
  # (Should already be catched by
  # sysctl-options, if enabled)
  
  ${IPTABLES} -A ICMPOUTBOUND -p icmp \
  --icmp-type timestamp-request -j LDROP
  
  ${IPTABLES} -A ICMPOUTBOUND -p icmp \
  --icmp-type timestamp-reply -j LDROP

    # Block ICMP-address-mask
  # (can help to prevent OS-fingerprinting)

    ${IPTABLES} -A ICMPOUTBOUND -p icmp \
  --icmp-type address-mask-request -j LDROP

    ${IPTABLES} -A ICMPOUTBOUND -p icmp \
  --icmp-type address-mask-reply -j LDROP

    # Accept all other ICMP going out
    
  ${IPTABLES} -A ICMPOUTBOUND -p icmp -j ACCEPT

#
# TOS target
# 
# The TOS target is used to set the Type of Service field within
# the IP header. The TOS field consists of 8 bits which are used
# to help in routing packets. This is one of the fields that can
# be used directly within iproute2 and its subsystem for routing
# policies. Worth noting, is that that if you handle several
# separate firewalls and routers, this is the only way to propagate
# routing information within the actual packet between these routers
# and firewalls. As previously noted, the MARK target - which sets
# a MARK associated with a specific packet
# - is only available within the kernel, and can not be propagated
# with the packet. If you feel a need to propagate routing information
# for a specific packet or stream, you should therefore
# set the TOS field, which was developed for this.
#
# There are currently a lot of routers on the Internet which do a
# pretty bad job at this, so as of now it may prove to be a bit
# useless to attempt TOS mangling before sending the packets on
# to the Internet. At best the routers will not pay any attention
# to the TOS field. At worst, they will look at the TOS field and 
# do the wrong thing. However, as stated above, the TOS field can
# most definitely be put to good use if you have a large WAN or
# LAN with multiple routers. You then in fact have the possibility
# of giving packets different routes and preferences, based on their
# TOS value - even though this might be confined to your own network.
#
# CAUTION:
#
# The TOS target is only capable of setting specific values,
# or named values on packets. These predefined TOS values can
# be found in the kernel include files, or more precisely,
# the Linux/ip.h file. The reasons are many, and you should
# actually never need to set any other values; however,
# there are ways around this limitation. To get around the
# limitation of only being able to set the named values on
# packets, you can use the FTOS patch available at the
# Paksecured Linux Kernel patches site maintained by
# Matthew G. Marsh. However, be cautious with this patch!
# You should not need to use any other than the default values,
# except in extreme cases.
#
# NOTE:
#
# Note that this target is only valid within the mangle
# table and can not be used outside it.
#
# NOTE:
#
# Also note that some old versions (1.2.2 or below) of
# iptables provided a broken implementation of this
# target which did not fix the packet checksum upon
# mangling, hence rendered the packets bad and in need
# of retransmission. That in turn would most probably
# lead to further mangling and the connection never working.
#
# The TOS target only takes one option as described below.
#
# OPTION: --set-tos
# EXAMPLE:
#
# iptables -t mangle -A PREROUTING -p TCP --dport 22 -j TOS \
# --set-tos 0x10
# 
# EXPLANATION:
#
# The --set-tos option tells the TOS mangler what TOS value
# to set on packets that are matched. The option takes a
# numeric value, either in hex or in decimal value.
# As the TOS value consists of 8 bits, the value may be 0-255,
# or in hex 0x00-0xFF. Note that in the standard TOS target you
# are limited to using the named values available
# (which should be more or less standardized),
# as mentioned in the previous warning.
# These values are Minimize-Delay (decimal value 16, hex value 0x10),
# Maximize-Throughput (decimal value 8, hex value 0x08),
# Maximize-Reliability (decimal value 4, hex value 0x04),
# Minimize-Cost (decimal value 2, hex 0x02) or Normal-Service
# (decimal value 0, hex value 0x00). The default value on most
# packets is Normal-Service, or 0.
# Note that you can, of course, use the actual names instead
# of the actual hex values to set the TOS value; in fact this
# is generally to be recommended, since the values associated
# with the names may be changed in future. For a complete listing
# of the "descriptive values", do an iptables -j TOS -h.
# This listing is complete as of iptables 1.2.5
# and should hopefully remain so for a while.
#
# Minimize-Delay 16 (0x10)
# Maximize-Throughput 8 (0x08)
# Maximize-Reliability 4 (0x04)
# Minimize-Cost 2 (0x02)
# Normal-Service 0 (0x00)
#
# - Most of these are the RFC 1060/1349 suggested TOS values, yours might vary.
# - To view mangle table, type: iptables -L -t mangle

# MANGLEPREROUTING

  ${IPTABLES} -t mangle -N MANGLEPREROUTING

  # FTP-DATA
  ${IPTABLES} -t mangle -A MANGLEPREROUTING -p tcp \
  --dport 20 -j TOS --set-tos 8

  # FTP
  ${IPTABLES} -t mangle -A MANGLEPREROUTING -p tcp \
  --dport 21 -j TOS --set-tos 16

  # SSH
  ${IPTABLES} -t mangle -A MANGLEPREROUTING -p tcp \
  --dport 22 -j TOS --set-tos 16

  # TELNET :.(
  ${IPTABLES} -t mangle -A MANGLEPREROUTING -p tcp \
  --dport 23 -j TOS --set-tos 16

  # SMTP
  ${IPTABLES} -t mangle -A MANGLEPREROUTING -p tcp \
  --dport 25 -j TOS --set-tos 16

  # DNS
  ${IPTABLES} -t mangle -A MANGLEPREROUTING -p tcp \
  --dport 53 -j TOS --set-tos 16

  # DNS
  ${IPTABLES} -t mangle -A MANGLEPREROUTING -p udp \
  --dport 53 -j TOS --set-tos 16

  # HTTP
  ${IPTABLES} -t mangle -A MANGLEPREROUTING -p tcp \
  --dport 80 -j TOS --set-tos 8

  # HTTP
  ${IPTABLES} -t mangle -A MANGLEPREROUTING -p tcp \
  --dport 8080 -j TOS --set-tos 8

  # SSL
  ${IPTABLES} -t mangle -A MANGLEPREROUTING -p tcp \
  --dport 443 -j TOS --set-tos 4

# MANGLEOUTPUT

  ${IPTABLES} -t mangle -N MANGLEOUTPUT

  # - Most of these are the RFC 1060/1349 suggested TOS values,
  # yours might vary.

  ${IPTABLES} -t mangle -A MANGLEOUTPUT -p tcp \
  --dport 20 -j TOS --set-tos 8

  ${IPTABLES} -t mangle -A MANGLEOUTPUT -p tcp \
  --dport 21 -j TOS --set-tos 16

  ${IPTABLES} -t mangle -A MANGLEOUTPUT -p tcp \
  --dport 22 -j TOS --set-tos 16

  ${IPTABLES} -t mangle -A MANGLEOUTPUT -p tcp \
  --dport 23 -j TOS --set-tos 16

  ${IPTABLES} -t mangle -A MANGLEOUTPUT -p tcp \
  --dport 25 -j TOS --set-tos 16

  ${IPTABLES} -t mangle -A MANGLEOUTPUT -p tcp \
  --dport 53 -j TOS --set-tos 16

  ${IPTABLES} -t mangle -A MANGLEOUTPUT -p udp \
  --dport 53 -j TOS --set-tos 16

  ${IPTABLES} -t mangle -A MANGLEOUTPUT -p tcp \
  --dport 80 -j TOS --set-tos 8

  ${IPTABLES} -t mangle -A MANGLEOUTPUT -p tcp \
  --dport 8080 -j TOS --set-tos 8

  ${IPTABLES} -t mangle -A MANGLEOUTPUT -p tcp \
  --dport 443 -j TOS --set-tos 4
  
#__END__
