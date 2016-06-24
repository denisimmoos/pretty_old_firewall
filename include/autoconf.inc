#!/bin/bash
# FILE: autoconf.inc
# DESC: Autoconfiguration of interfaces with ifconfig
#
# DATE: 08.09.2006
# AUTOR: Denis Immoos

# GET ALL INTERFACES
interfaces=`${IFCONFIG} | ${GREP} ^[^\ ] | ${AWK} '{print $1}'`

# SEARCH STRINGS
inet_addr="inet addr:"
mask="Mask:"
bcast="Bcast:"
mac="Link encap:"

echo "AUTOMATIC CONFIGURATION ..."

# CONFIGURE INTERFACES
# SET COUNTER $c
c="0"

for each in ${interfaces}
do
  
  # SET NAME
  interface[$c]=${each}

  echo "CONFIGURE (\${interface[$c]}=${interface[$c]}):"

  # IP ADDRESS
  interface_ip[$c]=`${IFCONFIG} ${interface[$c]} \
                    | ${GREP} "$inet_addr" \
                    | ${AWK} '{print $2}' \
                    | ${AWK} -F":" '{print $2}'`

  echo "        IP ADDRESS: ${interface_ip[$c]}"
  # CHECK IP
  f_check_ip ${interface_ip[$c]}

  # SUBNET MASK
  interface_subnet_mask[$c]=`${IFCONFIG} ${interface[$c]} \
                              | ${GREP} "$mask" \
                              | ${AWK} '{print $4}' \
                              | ${AWK} -F":" '{print $2}'`

  # SUBNET MASK SECOND TRY FOR LOOPBACK
  if [ -z "${interface_subnet_mask[$c]}" ];then

    interface_subnet_mask[$c]=`${IFCONFIG} ${interface[$c]} \
                                | ${GREP} "$mask" \
                                | ${AWK} '{print $3}' \
                                | ${AWK} -F":" '{print $2}'`
  
  fi

  echo "        SUBNET MASK: ${interface_subnet_mask[$c]}"
  # CHECK IP
  f_check_ip ${interface_subnet_mask[$c]}


  # BROADCAST ADDRESS
  interface_broadcast[$c]=`${IFCONFIG} ${interface[$c]} \
                          | ${GREP} "$bcast" \
                          | ${AWK} '{print $3}' \
                          | ${AWK} -F":" '{print $2}'`
  
  echo "        BROADCAST ADDRESS: ${interface_broadcast[$c]}"
  # CHECK IP
  f_check_ip ${interface_broadcast[$c]}
  
  # NETWORK ADDRESS
  interface_network[$c]=`${ROUTE} -n \
                          | ${GREP} -v UG \
                          | ${GREP} ${interface[$c]} \
                          | ${AWK} '{print $1}'`
  
  echo "        NETWORK ADDRESS: ${interface_network[$c]}"
  # CHECK IP
  f_check_ip ${interface_network[$c]}

  # MAC ADRESS
  interface_mac[$c]=`${IFCONFIG} ${interface[$c]} \
                    | ${GREP} "$mac" \
                    | ${AWK} '{print $5}'`
  
  echo "        MAC ADDRESS: ${interface_mac[$c]}"

  # COUNT
  let c=$c+1

done

# UNSET COUNTER AND EACH
unset c
unset each

# THERE MUST BE AT LEAST 2 INTERFACES
if [  ${#interface[@]} -lt '2' ];then
	f_error "ONLY 1 LOOPBACK DEVICE FOUND (firewalling not possible)"
elif [  ${#interface[@]} -eq '2' ];then
	f_warning "ONLY 1 ETHERNET DEVICES FOUND (forwarding not possible)"
else
	# COUNT INTERFACES
	echo "INTERFACES FOUND (${#interface[@]}) ..." 
fi

# DEFAULT GATEWAY
default_gateway=`${ROUTE} -n \
                | ${GREP} UG \
                | ${AWK} '{print $2}'`
  
if [ -n "$default_gateway" ];then
  echo "DEFAULT GATEWAY ($default_gateway) ..."
else
  f_warning "NO DEFAULT GATEWAY FOUND"
fi

#__END__
