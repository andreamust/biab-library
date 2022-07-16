"""
File for testing BIAB files.
"""
import biab_converter

BIAB_FILE = "/media/buzz/data/andrea/allBiabData/Night Dreamer_id_01945_community.Mgh"

abc = biab_converter.biab_meta(BIAB_FILE)

print(abc)
