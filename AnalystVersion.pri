AnalystVersion = $$system(git --git-dir $$PWD/.git --work-tree $$PWD describe --always --tags)
DEFINES += ANALYST_VERSION=\\\"$$AnalystVersion\\\"
