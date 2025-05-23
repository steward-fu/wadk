# (C) Copyright 1999-2000 Microsoft Corporation

# The name of this module. For our purposes it must be all in caps.
package COMPUTER;

    use strict;                # Keep the code clean
    #---------------------------------------------------#
    # Module level variables
    #---------------------------------------------------#
    my($Version) = "5.1.2432.0"; # Version of this file
    my($Current_INF_File);     # Stores name of the current INF file.
    my($Current_HTM_File);     # Name of the output file to use.
    my(@Device_Class_Options); # Array to store device specific options.
    my $CurrentINF;

#---------------------------------------------------#
# Routine for checking device class specific
# directives that occur in common sections verified
# by ChkINF.  Return 0 if directive is unknown or
# 1 if the directive is known (you should also verify
# it and write any appropriate warnings/errors.
#---------------------------------------------------#
sub DCDirective {
    return(0); # return 1 on success
}

#---------------------------------------------------#
# The module's main checking routine.
# This is your entry point for verifying an INF
#---------------------------------------------------#
sub InfCheck {
    return(1); # return 1 on success
}

#---------------------------------------------------#
# Verifies that the module loaded correctly.  Be sure
# to change the string to the name of your module.
#---------------------------------------------------#
sub Exists {
    print(STDERR "Module \"COMPUTER\" Loaded\n");
    return(1); # return 1 on success
}

#---------------------------------------------------#
# Is called when module is first included.
# Use it to set your per-inf variables.
#---------------------------------------------------#
sub InitGlobals {
    return(1); # return 1 on success
}


#---------------------------------------------------#
# Allows to add Device specific information to the
# top of the INF summary page.  The information here
# should be brief and link to detailed summaries
# below. (Which will be written using PrintDetials).
#---------------------------------------------------#
sub PrintHeader {
    return(1); # return 1 on success
}


#---------------------------------------------------#
# Allows addition of device specific results to the
# detail section on the INF summary.
#---------------------------------------------------#
sub PrintDetails {
    return(1); # return 1 on success
}

return(1); # Module must return 1 to let chkinf know it loaded correctly.
