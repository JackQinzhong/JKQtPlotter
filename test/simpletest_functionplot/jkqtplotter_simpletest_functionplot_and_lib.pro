TEMPLATE = subdirs

SUBDIRS +=  jkqtplotterlib jkqtplotter_simpletest_functionplot

jkqtplotterlib.file = ../../lib/jkqtplotterlib.pro

jkqtplotter_simpletest_functionplot.file=$$PWD/jkqtplotter_simpletest_functionplot.pro
jkqtplotter_simpletest_functionplot.depends = jkqtplotterlib
