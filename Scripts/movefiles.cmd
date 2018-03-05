@echo off

echo ---------- Moving Build Files ----------

rd /s /q %jsdst%
mkdir %jsdst%
xcopy %jssrc% %jsdst% /e

echo ---------- Finished Moving Files ----------