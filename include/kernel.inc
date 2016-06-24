#!/bin/bash
# FILE: kernel.inc
# DESC: Include kernel settings
# DATE: 08.09.2006
# AUTOR: Denis Immoos


# ip_

	#
	# Enable forwarding in kernel
	#
	# ip_forward
	echo "1" > /proc/sys/net/ipv4/ip_forward
	
	#
	# Set out local port range
	#
	# ip_local_port_range
	echo "32768 61000" > /proc/sys/net/ipv4/ip_local_port_range

	# ip_autoconfig
	# echo "0" > /proc/sys/net/ipv4/ip_autoconfig

	# ip_dynaddr
	# echo "0" > /proc/sys/net/ipv4/ip_dynaddr

	# ip_no_pmtu_disc
	# echo "0" > /proc/sys/net/ipv4/ip_no_pmtu_disc

	# ip_conntrack_max
	# echo "16376" > /proc/sys/net/ipv4/ip_conntrack_max

	# ip_nonlocal_bind
	# echo "0" > /proc/sys/net/ipv4/ip_nonlocal_bind

	# ip_default_ttl
	# echo "64" > /proc/sys/net/ipv4/ip_default_ttl

# icmp_

	#
	# Disable icmp 
	#
	# icmp_echo_ignore_all
	# echo "0" > /proc/sys/net/ipv4/icmp_echo_ignore_all

	#
	# Broadcast echo protection
	#
	# icmp_echo_ignore_broadcasts
	echo "1" > /proc/sys/net/ipv4/icmp_echo_ignore_broadcasts

	#
	# Enable bad error message protection
	#
	# icmp_ignore_bogus_error_responses
	echo "1" > /proc/sys/net/ipv4/icmp_ignore_bogus_error_responses

	# icmp_ratelimit
	# echo "100" > /proc/sys/net/ipv4/icmp_ratelimit
	
	# icmp_ratemask
	# echo "6168" > /proc/sys/net/ipv4/icmp_ratemask

# tcp_

	#
	# Kill timestamps
	#
	# tcp_timestamps
	echo "0" > /proc/sys/net/ipv4/tcp_timestamps

	#
	# Enable SYN Cookies
	#
	# tcp_syncookies
	echo "1" > /proc/sys/net/ipv4/tcp_syncookies

	#
	# Reduce DoS'ing ability by reducing timeouts
	#
	# tcp_fin_timeout
	echo "30" > /proc/sys/net/ipv4/tcp_fin_timeout

	# tcp_window_scaling
	echo "0" > /proc/sys/net/ipv4/tcp_window_scaling

	# tcp_keepalive_time
	echo "2400" > /proc/sys/net/ipv4/tcp_keepalive_time

	# tcp_sack
	echo "0" > /proc/sys/net/ipv4/tcp_sack

	# tcp_abort_on_overflow
	# echo "0" > /proc/sys/net/ipv4/tcp_abort_on_overflow

	# tcp_low_latency
	# echo "0" > /proc/sys/net/ipv4/tcp_low_latency

	# tcp_rmem
	# echo "4096	87380	174760" > /proc/sys/net/ipv4/tcp_rmem

	# tcp_adv_win_scale
	# echo "2" > /proc/sys/net/ipv4/tcp_adv_win_scale

	# tcp_max_orphans
	# echo "8192" > /proc/sys/net/ipv4/tcp_max_orphans

	# tcp_app_win
	# echo "31" > /proc/sys/net/ipv4/tcp_app_win

	# tcp_max_syn_backlog
	# echo "1024" > /proc/sys/net/ipv4/tcp_max_syn_backlog

	# tcp_stdurg
	# echo "0" > /proc/sys/net/ipv4/tcp_stdurg

	# tcp_dsack
	# echo "1" > /proc/sys/net/ipv4/tcp_dsack

	# tcp_max_tw_buckets
	# echo "180000" > /proc/sys/net/ipv4/tcp_max_tw_buckets

	# tcp_syn_retries
	# echo "5" > /proc/sys/net/ipv4/tcp_syn_retries

	# tcp_ecn
	# echo "0" > /proc/sys/net/ipv4/tcp_ecn

	# tcp_mem
	# echo "48128	48640	49152" > /proc/sys/net/ipv4/tcp_mem

	# tcp_synack_retries
	# echo "5" > /proc/sys/net/ipv4/tcp_synack_retries

	# tcp_fack
	# echo "1" > /proc/sys/net/ipv4/tcp_fack

	# tcp_orphan_retries
	# echo "0" > /proc/sys/net/ipv4/tcp_orphan_retries

	# tcp_reordering
	# echo "3" > /proc/sys/net/ipv4/tcp_reordering

	# tcp_frto
	# echo "0" > /proc/sys/net/ipv4/tcp_frto

	# tcp_retrans_collapse
	# echo "1" > /proc/sys/net/ipv4/tcp_retrans_collapse

	# tcp_tw_recycle
	# echo "0" > /proc/sys/net/ipv4/tcp_tw_recycle

	# tcp_keepalive_intvl
	# echo "75" > /proc/sys/net/ipv4/tcp_keepalive_intvl

	# tcp_retries1
	# echo "3" > /proc/sys/net/ipv4/tcp_retries1

	# tcp_tw_reuse
	# echo "0" > /proc/sys/net/ipv4/tcp_tw_reuse

	# tcp_keepalive_probes
	# echo "9" > /proc/sys/net/ipv4/tcp_keepalive_probes

	# tcp_retries2
	# echo "15" > /proc/sys/net/ipv4/tcp_retries2

	# tcp_rfc1337
	# echo "0" > /proc/sys/net/ipv4/tcp_rfc1337

	# tcp_wmem
	# echo "4096	16384	131072" > /proc/sys/net/ipv4/tcp_wmem

# accept_

	#
	# Kill redirects
	#
	# accept_redirects
	echo "0" > /proc/sys/net/ipv4/conf/all/accept_redirects

	#
	# Source routed Packages
	#
	# accept_source_route
	echo "0" > /proc/sys/net/ipv4/conf/all/accept_source_route

# send_

	#
	# Send Redirect Messages
	#
	# send_redirects
	echo "0" > /proc/sys/net/ipv4/conf/all/send_redirects

# log_

	#
	# Log martians (packets with impossible addresses)
	#
	# log_martians
	echo "1" > /proc/sys/net/ipv4/conf/all/log_martians

# rp_

	#
	# Drop Spoofed Packets comming in on an interface,
	# which if replied to, would result in the reply
	# going out a different interface
	# Disabling IP Spoofing attacks.
	#
	# rp_filter
	echo "1" > /proc/sys/net/ipv4/conf/all/rp_filter

#__END__