SUBFOLDERS := exosphere fusee stratosphere thermosphere

TOPTARGETS := all clean

$(TOPTARGETS): $(SUBFOLDERS)

$(SUBFOLDERS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

fusee: exosphere thermosphere stratosphere
 
.PHONY: $(TOPTARGETS) $(SUBFOLDERS)
