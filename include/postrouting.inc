#!/bin/bash
# FILE: accept_allout.inc
# DESC:accept_allout RULES
# DATE: 08.09.2006
# AUTOR: Denis Immoos

# HAND CODED RULES ONLY

#
# MASQUERADE target 
#
# The MASQUERADE target is used basically the same as the SNAT target,
# but it does not require any --to-source option.
# The reason for this is that the MASQUERADE target was made to work with,
# for example, dial-up connections, or DHCP connections,
# which gets dynamic IP addresses when connecting to the network in question.
# This means that you should only use the MASQUERADE target with dynamically
# assigned IP connections, 
# which we don't know the actual address of at all times.
# If you have a static IP connection, you should instead use the SNAT target. 
#
# When you masquerade a connection, it means that we set the IP address used 
# on a specific network interface instead of the --to-source option,
# and the IP address is automatically grabbed from the information
# about the specific interface. The MASQUERADE target also has the
# effect that connections are forgotten when an interface goes down,
# which is extremely good if we, for example, kill a specific interface.
# If we would have used the SNAT target, we may have been left with a lot
# of old connection tracking data, which would be lying around for days,
# swallowing up worth-full connection tracking memory. This is in general
# the correct behavior when dealing with dial-up lines that are probable
# to be assigned a different IP every time it is brought up.
# In case we are assigned a different IP, the connection is lost anyways,
# and it is more or less idiotic to keep the entry around. 
#
# It is still possible to use the MASQUERADE target instead of
# SNAT even though you do have an static IP, however,
# it is not favorable since it will add extra overhead,
# and there may be inconsistencies in the future which will
# thwart your existing scripts and render them "unusable". 
#
# Note that the MASQUERADE target is only valid within the
# POSTROUTING chain in the nat table, just as the SNAT target.
# The MASQUERADE target takes one option specified below, which is optional. 
#
# OPTION: --to-ports 
#
# EXAMPLE : 
#
# iptables -t nat -A POSTROUTING -p tcp -j MASQUERADE --to-ports 1024-31000 
#
# EXPLANATION:
#
# The --to-ports option is used to set the source port 
# or ports to use on outgoing packets. Either you can specify a single port like
# --to-ports 1025 or you may specify a port range as --to-ports 1024-3000.
# In other words, the lower port range delimiter and the upper port range
# delimiter separated with a hyphen.
# This alters the default SNAT port-selection as described in the
# SNAT target section. The --to-ports option is only valid if the rule match
# section specifies the TCP or UDP protocols with the --protocol match.  

	
	# MASQUERADE EXAMPLES :

	# Masquerade only  
	# from Internal Interface INTERNAL_INTERFACE 
	# to External Interface EXTERNAL_INTERFACE 
  		
	# ${IPTABLES} -A POSTROUTING -t nat -i INTERNAL_INTERFACE \
	# -o EXTERNAL_INTERFACE -j MASQUERADE
	
	# The source interface "-i eth0" must be an INTERNAL Interface !!!
	# ${IPTABLES} -A POSTROUTING -t nat -i eth3 -o eth0 -j MASQUERADE

	
#
# SNAT target
#
# The SNAT target is used to do Source Network Address Translation,
# which means that this target will rewrite the Source
# IP address in the IP header of the packet. This is what we want, for example,
# when several hosts have to share an Internet connection.
# We can then turn on ip forwarding in the kernel, and write an SNAT rule which
# will translate all packets going out from our local network to the source
# IP of our own Internet connection. Without doing this, the outside world would
# not know where to send reply packets, since our local networks mostly use the
# IANA specified IP addresses which are allocated for LAN networks.
# If we forwarded these packets as is, no one on the Internet
# would know that they where actually from us.
# The SNAT target does all the translation needed to do this kind of work,
# letting all packets leaving our LAN look as if they came from a single host,
# which would be our firewall. 
#
# The SNAT target is only valid within the nat table, 
# within the POSTROUTING chain.
# This is in other words the only chain in which you may use SNAT.
# Only the first packet in a connection is mangled by SNAT,
# and after that all future packets using the same connection 
# will also be SNATted.
# Furthermore, the initial rules in the POSTROUTING chain
# will be applied to all the packets in the same stream. 
#
# OPTION: --to-source 
#
# EXAMPLE: 
#
# iptables -t nat -A POSTROUTING -p tcp -o eth0 -j SNAT \
# --to-source 194.236.50.155-194.236.50.160:1024-32000  
#
# EXPLANATION:
#
# The --to-source option is used to specify which source the packet should use.
# This option, at its simplest, takes one IP address which we want to use for 
# the source IP address in the IP header.
# If we want to balance between several IP addresses, we can use a range of
# IP addresses, separated by a hyphen. The --to--source IP numbers could then,
# for instance, be something like in the above example:
# 194.236.50.155-194.236.50.160.
# The source IP for each stream that we open would then be allocated
# randomly from these, and a single stream would always use the same IP address
# for all packets within that stream.
# We can also specify a range of ports to be used by SNAT. All the source ports
# would then be confined to the ports specified.
# The port bit of the rule would then look like in the example above,
# :1024-32000. This is only valid if -p tcp or -p udp was specified
# somewhere in the match of the rule in question.
# iptables will always try to avoid making any port alterations if possible,
# but if two hosts try to use the same ports, iptables will map one of them to
# another port.
# If no port range is specified, then if they're needed,
# all source ports below 512 will be mapped to other ports below 512.
# Those between source ports 512 and 1023 will be mapped  to ports below 1024.
# All other ports will be mapped to 1024 or above. As previously stated,
# iptables will always try to maintain the source ports used by the actual 
# workstation making the connection.
# Note that this has nothing to do with destination ports, so if a client tries
# to make contact with an HTTP server outside the firewall,
# it will not be mapped to the FTP control port.  

	# SNAT EXAMPLES
	
	# With IP-ADDRESSES
	#
	# ${IPTABLES} -A POSTROUTING -t nat \
	# -s INTERNAL_NETWORK -o eth0 -j SNAT
	#
	# ${IPTABLES} -A POSTROUTING -t nat \
	# -s 10.10.1.32/255.255.255.0 -0 eth0 -j SNAT

#__END__
