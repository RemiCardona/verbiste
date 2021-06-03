# $Id: Makefile.am,v 1.38 2019/08/20 23:47:38 sarrazip Exp $

libdatadir = $(datadir)/$(PACKAGE)-$(API)

bin_PROGRAMS = french-conjugator french-deconjugator

if BUILD_CONSOLE_APP
bin_PROGRAMS += verbiste-console
endif BUILD_CONSOLE_APP

french_deconjugator_SOURCES = \
	french-deconjugator.cpp \
	Command.cpp \
	Command.h

french_deconjugator_CXXFLAGS = \
	$(LIBXML2_CFLAGS) \
	-DCOPYRIGHT_YEARS=\"$(COPYRIGHT_YEARS)\" \
	-DLIBDATADIR=\"$(libdatadir)\" \
	-I$(top_srcdir)/src

french_deconjugator_LDADD = \
	$(LIBXML2_LIBS) \
	../verbiste/libverbiste-$(API).la

french_conjugator_SOURCES = \
	french-conjugator.cpp \
	Command.cpp \
	Command.h

french_conjugator_CXXFLAGS = \
	$(LIBXML2_CFLAGS) \
	-DCOPYRIGHT_YEARS=\"$(COPYRIGHT_YEARS)\" \
	-DLIBDATADIR=\"$(libdatadir)\" \
	-I$(top_srcdir)/src

french_conjugator_LDADD = \
	$(LIBXML2_LIBS) \
	../verbiste/libverbiste-$(API).la

if BUILD_CONSOLE_APP

verbiste_console_SOURCES = console-app.cpp

verbiste_console_CXXFLAGS = \
	$(LIBXML2_CFLAGS) \
	-DPACKAGE_FULL_NAME=\"$(PACKAGE_FULL_NAME)\" \
	-DCOPYRIGHT_YEARS=\"$(COPYRIGHT_YEARS)\" \
	-DGETTEXT_PACKAGE=\"$(PACKAGE)\" \
	-DLOCALEDIR=\"$(localedir)\" \
	-DLIBDATADIR=\"$(libdatadir)\" \
	-I../intl -I$(top_srcdir)/intl \
	-I$(top_srcdir)/src

verbiste_console_LDADD = \
	$(LIBXML2_LIBS) \
	../verbiste/libverbiste-$(API).la \
	../gui/libconjugation.la

endif BUILD_CONSOLE_APP

# This makefile is supposed to be encoded in UTF-8 in lines
# where $(LU) is used.
# Setting LC_ALL is necessary on Solaris.
#
ENV = LIBDATADIR=$(top_srcdir)/data
LU = $(ENV) LANG=en_US.UTF-8 LC_ALL=en_US.UTF-8

.PHONY: check-fr check-it

check-fr: check-console
if HAVE_GETOPT_LONG
	test "`$(LU) ./french-deconjugator --version`" = \
				"french-deconjugator $(VERSION)"
	@echo "Testing exit status when requesting help page:"
	$(LU) ./french-deconjugator --help 2>&1 >/dev/null
	@echo "Testing exit status when passing unknown option:"
	if $(LU) ./french-deconjugator --unknown 2>&1 >/dev/null; then exit 1; fi 2>&1 >/dev/null
	test "`$(LU) ./french-conjugator --version`" = \
				"french-conjugator $(VERSION)"
	@echo "Testing exit status when requesting help page:"
	$(LU) ./french-conjugator --help 2>&1 >/dev/null
	@echo "Testing exit status when passing unknown option:"
	if $(LU) ./french-conjugator --unknown 2>&1 >/dev/null; then exit 1; fi 2>&1 >/dev/null
	test "`$(LU) ./french-conjugator --pronouns hacher | grep ^j | head -1`" = "je hache"
	test "`$(LU) ./french-conjugator --pronouns habiter | grep ^j | head -1`" = "j'habite"
endif
	test "`echo aimerions | $(LU) ./french-deconjugator`" = "aimer, conditional, present, 1, plural"
	test "`$(LU) ./french-deconjugator aimerions`" = "aimer, conditional, present, 1, plural"
	test "`echo UNKNOWN_VERB | $(LU) ./french-deconjugator`" = ""
	test "`echo etre | $(LU) ./french-deconjugator`" = ""
	test "`$(LU) ./french-deconjugator UNKNOWN_VERB`" = ""
	test "`$(LU) ./french-deconjugator ete`" = ""
	test "`$(LU) ./french-deconjugator fus | wc -l`" -eq 3
	test "`$(LU) ./french-deconjugator parais | wc -l`" -eq 6
	test "`$(LU) ./french-deconjugator aléseraient`" = "aléser, conditional, present, 3, plural"
	test "`$(LU) ./french-deconjugator harcellerions`" = "harceler, conditional, present, 1, plural"
	test "`$(LU) ./french-deconjugator harcèlerions`" = "harceler, conditional, present, 1, plural"
	test "`echo asseoir | $(LU) ./french-conjugator | grep asseyerai,`" = "assiérai, asseyerai, assoirai"
	test "`$(LU) ./french-conjugator zézayer | grep zaieraient`" = "zézaieraient, zézayeraient"
	test "`$(LU) ./french-conjugator échoir | grep -c chy`" -eq 0
	test "`$(LU) ./french-conjugator déchoir | grep -c chy`" -eq 0
	test "`$(LU) ./french-conjugator surseoir sursoir | wc -l `" -eq 126
	test "`$(LU) ./french-conjugator zézayer | grep zézaieraient`" = "zézaieraient, zézayeraient"
	test "`$(LU) ./french-conjugator --mode=subjunctive avoir | wc -l`" -eq 15
	test "`$(LU) ./french-conjugator --tense=present avoir | wc -l`" -eq 30
	test "`$(LU) ./french-conjugator --mode=subjunctive --tense=imperfect avoir | wc -l`" -eq 8
	test "`$(LU) ./french-conjugator --mode=subjunctive,indicative --tense=imperfect avoir | wc -l`" -eq 15
	test "`$(LU) ./french-conjugator --mode=subjunctive --tense=imperfect,present avoir | wc -l`" -eq 15
	test "`$(LU) ./french-conjugator --mode=subjunctive,indicative --tense=imperfect,present avoir | wc -l`" -eq 29
	test "`$(LU) ./french-conjugator --mode=subjunctive,indicative --tense=imperfect,present avoir être | wc -l`" -eq 58
	$(LU) ./french-conjugator --mode=xxx avoir 2>&1 | grep -q 'invalid mode xxx'
	$(LU) ./french-conjugator --tense=xxx avoir 2>&1 | grep -q 'invalid tense xxx'
	$(LU) $(PERL) $(srcdir)/check-infinitives.pl $(top_srcdir)/data/verbs-fr.xml
	$(LU) ./french-conjugator --all-infinitives > all-infinitives.c.txt
	$(LU) ./french-deconjugator --all-infinitives > all-infinitives.d.txt
	diff -q all-infinitives.c.txt all-infinitives.d.txt
	test `wc -l < all-infinitives.c.txt` -gt 7000
	rm all-infinitives.c.txt all-infinitives.d.txt

check-console:
if BUILD_CONSOLE_APP
	echo avoir | $(LU) ./verbiste-console | grep -q "^<result input='avoir'>$$"
	test "`echo avoir | $(LU) ./verbiste-console | wc -l`" -eq 77
	test "`echo a | $(LU) ./verbiste-console | wc -l`" -eq 77
	test "`echo ete | $(LU) ./verbiste-console | wc -l`" -eq 77
	test "`echo ete | $(LU) ./verbiste-console | grep -c '^*'`" -eq 1
	test "`echo parais | $(LU) ./verbiste-console | wc -l`" -eq 152
	test "`echo parais | $(LU) ./verbiste-console | grep -wc conjugation`" -eq 4
	test "`echo parais | $(LU) ./verbiste-console | grep -wc conjugation`" -eq 4
	test "`echo parais | $(LU) ./verbiste-console | grep -c '^*'`" -eq 5
	test "`echo entrainer | $(LU) ./verbiste-console | grep -c ^entrai`" -eq 0
	test "`echo entrainer | $(LU) ./verbiste-console | grep -c ^entraî`" -eq 50
	test "`echo entraîner | $(LU) ./verbiste-console | grep -c ^entraî`" -eq 50
	echo -ne "A\n"                | $(LU) ./verbiste-console | grep -q "^eussiez"
	echo -ne "/hidepronouns\nA\n" | $(LU) ./verbiste-console | grep -q "^eussiez"
	echo -ne "/hp\nA\n"           | $(LU) ./verbiste-console | grep -q "^eussiez"
	echo -ne "/showpronouns\nA\n" | $(LU) ./verbiste-console | grep -q "^que vous eussiez"
	echo -ne "/sp\nA\n"           | $(LU) ./verbiste-console | grep -q "^que vous eussiez"
endif BUILD_CONSOLE_APP

check-it:
	test "`echo ha | $(LU) ./french-deconjugator --lang=it`" = "avere, indicative, present, 3, singular"
	test "`$(PERL) -e 'print qq{avr\xc3\xb2\n}' | $(LU) ./french-deconjugator --lang=it`" = "avere, indicative, future, 1, singular"
	test "`$(LU) ./french-deconjugator --lang=it partire | wc -l`" -eq 3
	test "`$(LU) ./french-deconjugator --data-dir=$(top_srcdir)/data --lang=it partire | wc -l`" -eq 3
	test "`$(LU) ./french-deconjugator --lang=it parto`"    = "partire, indicative, present, 1, singular"
	test "`$(LU) ./french-deconjugator --lang=it partisco`" = "partire, indicative, present, 1, singular"
	test "`$(LU) ./french-deconjugator --lang=it avendo`" = "avere, gerund, present, 0, singular"
	test "`$(LU) ./french-conjugator --lang=it avere | grep eberro`" = "eberro"
	test "`$(LU) ./french-conjugator --lang=it --pronouns avere | grep -c 'che essi avessero'`" -eq 1
	test "`$(LU) ./french-conjugator --lang=it avere sentire partire | grep -c '^-$$'`" -eq 4
	test "`$(LU) ./french-conjugator --data-dir=$(top_srcdir)/data --lang=it avere | grep eberro`" = "eberro"
	$(LU) $(PERL) $(srcdir)/check-infinitives.pl $(top_srcdir)/data/verbs-it.xml
	$(LU) ./french-conjugator --lang=it --all-infinitives > all-infinitives.c.txt
	$(LU) ./french-deconjugator --lang=it --all-infinitives > all-infinitives.d.txt
	diff -q all-infinitives.c.txt all-infinitives.d.txt
	test `wc -l < all-infinitives.c.txt` -gt 100
	rm all-infinitives.c.txt all-infinitives.d.txt

check: all check-fr check-it
	@echo "check: success."

check_PROGRAMS = check-constructors
TESTS = $(check_PROGRAMS)

# This program checks that the single-argument FrenchVerbDictionary constructor
# exists and can be linked with.
#
check_constructors_SOURCES = check-constructors.cpp
check_constructors_CXXFLAGS = $(LIBXML2_CFLAGS) -I$(top_srcdir)/src
check_constructors_LDADD= $(LIBXML2_LIBS) ../verbiste/libverbiste-$(API).la


EXTRA_DIST = check-infinitives.pl

MAINTAINERCLEANFILES = Makefile.in
