import os
import subprocess

if not "ConnectedVision" in os.environ:
	raise Exception("\"ConnectedVision\" environment variable is not defined")

cvDir = os.path.abspath(os.environ["ConnectedVision"])

if not os.path.isdir(cvDir):
	raise Exception("the directory path referenced by the ConnectedVision environment variable is invalid: " + cvDir)

toolsDir = os.path.join(cvDir, "tools")
targetDir = os.path.join(cvDir, "test", "UnitTest")
schemaFile = os.path.join(targetDir, "GeneratorTestCode.schema")
dirStructureFile = os.path.join(targetDir, "GeneratorTestCodeStructure.json")

print("")
print(schemaFile)
print("--------------------------------")
print("CreateItemsForSchema.js")
subprocess.check_call(["node", os.path.join(toolsDir, "CodeFromTemplate", "CreateItemForSchema.js"), targetDir, cvDir, schemaFile, dirStructureFile, "-id", "UnitTest"])
 
print("")
print("CodeFromTemplate.js - DATA items")
globalJson = os.path.join(targetDir, "global.json")
itemsJson = os.path.join(targetDir, "items.json")
subprocess.check_call(["node", os.path.join(toolsDir, "CodeFromTemplate", "CodeFromTemplate.js"), globalJson, itemsJson])

print("")
print("Clean Up")
subprocess.call(["rm", "-f", globalJson])
subprocess.call(["rm", "-f", itemsJson])
subprocess.call(["rm", "-f", os.path.join(targetDir, "artefacts.json")])

print("OK")
