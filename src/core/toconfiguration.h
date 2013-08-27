#ifndef TOCONFIGURATION_H
#define TOCONFIGURATION_H

#include "core/tora_export.h"

#include <loki/Singleton.h>
#include <QtCore/QStringList>
#include <QtCore/QMap>
#include <QtGui/QApplication>

typedef QMap<QString, bool> ToolsMap;
typedef QMap<QString, QString> HelpsMap;
typedef QMapIterator<QString, QString> HelpsMapIterator;
typedef QMap<QString, QString> ChartsMap;
typedef QMapIterator<QString, QString> ChartsMapIterator;
typedef QMap<QString, QString> TemplatesMap;
typedef QMapIterator<QString, QString> TemplatesMapIterator;
typedef QMap<QString, QVariant> EditorShortcutsMap;
typedef QMapIterator<QString, QVariant> EditorShortcutsMapIterator;
typedef QMap<QString, QString> ConnectionColors;
typedef QMapIterator<QString, QString> ConnectionColorsIterator;

class toConfigurationPrivate;

class TORA_EXPORT toConfiguration
{
    toConfigurationPrivate *p;

public:
    toConfiguration();
    ~toConfiguration();

    /* This enum represents various states from ObjectCache comboBox
     * database settings gui(see todatabasesettingui.ui).
     */
    enum ObjectCache
    {
        WHEN_NEEDED = 0,
        ON_CONNECT = 1,
        UNTIL_MANDATORY = 2,
        NEVER = 3
    };

    /*! \brief Set the QSettings access strings.
    QSettings uses these. It's used in the main.cpp before
    new QApplication instance init.
    The 2nd usage is in the toConfiguration constructor due
    some strange loading -- values are ignored with empty
    QSettings constructor (maybe due the Loki lib?) */
    static void setQSettingsEnv();

    /**
     * Save configuration to file.
     */
    void saveConfig(void);
    /**
    * Load a string to string map from file saved by the @ref saveMap function.
    * @param filename Filename to load
    * @param map Reference to the map to fill with the new values.
    */
    void loadMap(const QString &filename, std::map<QString, QString> &map);

    /**
    * A map containing the available configuration settings. By convention the
    * character ':' is used to separate parts of the path.
    *
    * @see globalConfig
    * @see globalSetConfig
    * @see config
    * @see setConfig
    */
    bool saveMap(const QString &file, std::map<QString, QString> &pairs);

    bool savePassword();
    void setSavePassword(bool v);

    int maxNumber();
    void setMaxNumber(int v);

    int maxColDisp();
    void setMaxColDisp(int v);

    QString textFont();
    void setTextFont(const QString & v);

    QString codeFont();
    void setCodeFont(const QString & v);

    QString listFont();
    void setListFont(const QString & v);

    QString refresh();
    void setRefresh(const QString & v);

    QString highlightType();
    void setHighlightType(QString v);

    bool keywordUpper();
    void setKeywordUpper(bool v);

    bool objectNamesUpper();
    void setObjectNamesUpper(bool v);

    QString cacheDir();
    void setCacheDir(const QString & v);

    bool cacheDisk();
    void setCacheDisk(bool v);

    QString sqlFile();
    void setSqlFile(const QString & v);

    int statusMessage();
    void setStatusMessage(int v);

    bool dbTitle();
    void setDbTitle(bool v);

    QString sizeUnit();
    void setSizeUnit(const QString & v);

    QString helpPath();
    void setHelpPath(const QString & v);

    int statusSave();
    void setStatusSave(int v);

    bool autoCommit();
    void setAutoCommit(bool v);

    bool changeConnection();
    void setChangeConnection(bool v);

    int connectSize();
    void setConnectSize(int v);

    QString defaultTool();
    void setDefaultTool(const QString & v);

    int chartSamples();
    void setChartSamples(int v);

    int displaySamples();
    void setDisplaySamples(int v);

    bool codeCompletion();
    void setCodeCompletion(bool v);

    bool completionSort();
    void setCodeCompletionSort(bool v);

    bool autoIndent();
    void setAutoIndent(bool v);

    bool dontReread();
    void setDontReread(bool v);

    bool messageStatusbar();
    void setMessageStatusbar(bool v);

    bool multiLineResults();
    void setMultiLineResults(bool v);

    bool colorizedConnections();
    void setColorizedConnections(bool v);

    ConnectionColors connectionColors();
    void setConnectionColors(const ConnectionColors & v);

    ObjectCache objectCache();
    void setObjectCache(ObjectCache v);

    bool firewallMode();
    void setFirewallMode(bool v);

    int connTestInterval();
    void setConnTestInterval(int v);

    int maxContent();
    void setMaxContent(int v);

    bool restoreSession();
    void setRestoreSession(bool v);

    QString defaultSession();
    void setDefaultSession(const QString & v);

    int defaultFormat();
    void setDefaultFormat(int v);

    bool autoIndentRo();
    void setAutoIndentRo(bool v);

    bool indicateEmpty();
    void setIndicateEmpty(bool v);

    QString indicateEmptyColor();
    void setIndicateEmptyColor(const QString & v);

    QString extensions();
    void setExtensions(const QString & v);

    int recentMax();

    QString lastDir();
    void setLastDir(const QString & v);

    QString locale();
    void setLocale(const QString & v);

    int keepAlive();
    void setKeepAlive(int v);

    int numberFormat();
    void setNumberFormat(int v);

    int numberDecimals();
    void setNumberDecimals(int v);

    int cacheTimeout();

    int tabStop();
    void setTabStop(int v);

    bool tabSpaces();
    void setTabSpaces(bool v);

    bool editDragDrop();
    void setEditDragDrop(bool v);

    bool toadBindings();
    void setToadBindings(bool v);

    bool displayGridlines();
    void setDisplayGridlines(bool v);

    QString style();
    void setStyle(const QString & v);

    // tooracleconnection
    QString oracleHome();
    void setOracleHome(QString const&);

    QString dateFormat();
    void setDateFormat(const QString & v);

    QString timestampFormat();
    void setTimestampFormat(const QString & v);

    int maxLong();
    void setMaxLong(int v);

    QString planTable(QString schema);
    void setPlanTable(const QString & v);

    bool keepPlans();
    void setKeepPlans(bool v);

    bool vsqlPlans();
    void setVsqlPlans(bool v);

    bool sharedPlan();
    void setSharedPlan(bool v);

    // toqsqlconnection
    QString mysqlHome();
    void setMysqlHome(QString const&);

    QString pgsqlHome();
    void setPgsqlHome(QString const&);

    bool onlyForward();
    void setOnlyForward(bool v);

    int createAction();
    void setCreateAction(int v);

    // main.cpp
    QString lastVersion();
    void setLastVersion(const QString & v);
    QString firstInstall();
    void setFirstInstall(const QString & v);
    QStringList recentFiles();
    void setRecentFiles(QStringList v);
    QByteArray mainWindowGeometry();
    void setMainWindowGeometry(QByteArray v);
    QByteArray mainWindowState();
    void setMainWindowState(QByteArray v);

    void setLeftDockbarState(QByteArray v);
    QByteArray leftDockbarState();
    void setRightDockbarState(QByteArray v);
    QByteArray rightDockbarState();

    // tools
    ToolsMap& tools();
    void setTools(ToolsMap &v);

    // toresultlistformat
    QString csvSeparator();
    QString csvDelimiter();

    // toeditextensions
    bool commaBefore();
    void setCommaBefore(bool v);

    bool blockOpenLine();
    void setBlockOpenLine(bool v);

    bool operatorSpace();
    void setOperatorSpace(bool v);

    bool rightSeparator();
    void setRightSeparator(bool v);

    bool endBlockNewline();
    void setEndBlockNewline(bool v);

    int commentColumn();
    void setCommentColumn(int v);

    // tobrowser
    bool filterIgnoreCase();
    void setFilterIgnoreCase(bool v);

    bool filterInvert();
    void setFilterInvert(bool v);

    int filterType();
    void setFilterType(int v);

    int filterTablespaceType();
    void setFilterTablespaceType(int v);

    QString filterText();
    void setFilterText(const QString & v);

    // tohelp
    HelpsMap additionalHelp();
    void setAdditionalHelp(HelpsMap v);

    // tochartmanager
    ChartsMap chartFiles();
    void setChartFiles(ChartsMap v);

    ChartsMap chartAlarms();
    void setChartAlarms(ChartsMap v);

    // toooutput
    QString polling();
    void setPolling(const QString & v );

    int logType();
    void setLogType(int v);

    QString logUser();
    void setLogUser(const QString & v);

    // torollback
    bool noExec();
    void setNoExec(bool v);

    bool needRead();
    void setNeedRead(bool v);

    bool needTwo();
    void setNeedTwo(bool v);

    bool alignLeft();
    void setAlignLeft(bool v);

    bool oldEnable();
    void setOldEnable(bool v);

    // tosgatrace
    bool autoUpdate();
    void setAutoUpdate(bool v);

    // tostorage
    bool dispTablespaces();
    void setDispTablespaces(bool v);

    bool dispCoalesced();
    void setDispCoalesced(bool v);

    bool dispExtents();
    void setDispExtents(bool v);

    bool dispAvailableGraph();
    void setDispAvailableGraph(bool v);

    // totemplate
    TemplatesMap templates();
    void setTemplates(TemplatesMap v);

    // totuning
    /*! True if there are no prefs for tuning.
    It's used when there is no m_tuningOverview defined in prefs. */
    bool tuningFirstRun();

    bool tuningOverview();
    void setTuningOverview(bool v);

    bool tuningFileIO();
    void setTuningFileIO(bool v);

    bool tuningWaits();
    void setTuningWaits(bool v);

    bool tuningCharts();
    void setTuningCharts(bool v);

    // toworksheet
    bool wsAutoSave();
    void setWsAutoSave(bool v);

    bool wsCheckSave();
    void setWsCheckSave(bool v);

    QString wsAutoLoad();
    void setWsAutoLoad(const QString & v);

    bool wsLogAtEnd();
    void setWsLogAtEnd(bool v);

    bool wsLogMulti();
    void setWsLogMulti(bool v);

    bool wsStatistics();
    void setWsStatistics(bool v);

    bool wsTimedStats();
    void setWsTimedStats(bool v);

    bool wsNumber();
    void setWsNumber(bool v);

    bool wsMoveToErr();
    void setWsMoveToErr(bool v);

    bool wsHistory();
    void setWsHistory(bool v);

    bool wsExecLog();
    void setWsExecLog(bool v);

    bool wsToplevelDescribe();
    void setWsToplevelDescribe(bool v);

    // tosyntaxsetup
    QColor syntaxDefault();
    void setSyntaxDefault(QColor v);
    QColor syntaxComment();
    void setSyntaxComment(QColor v);
    QColor syntaxNumber();
    void setSyntaxNumber(QColor v);
    QColor syntaxKeyword();
    void setSyntaxKeyword(QColor v);
    QColor syntaxString();
    void setSyntaxString(QColor v);
    QColor syntaxDefaultBg();
    void setSyntaxDefaultBg(QColor v);
    QColor syntaxDebugBg();
    void setSyntaxDebugBg(QColor v);
    QColor syntaxErrorBg();
    void setSyntaxErrorBg(QColor v);
    QColor syntaxCurrentLineMarker();
    void setSyntaxCurrentLineMarker(QColor v);
    QColor syntaxStaticBg();
    void setSyntaxStaticBg(QColor v);

    bool useMaxTextWidthMark();
    void setUseMaxTextWidthMark(bool v);
    int maxTextWidthMark();
    void setMaxTextWidthMark(int v);

    int connectionTestTimeout();
    void setConnectionTestTimeout(int v);

    // shortcut editor
    bool useEditorShortcuts();
    void setUseEditorShortcuts(bool v);
    EditorShortcutsMap editorShortcuts();
    void setEditorShortcuts(const EditorShortcutsMap & v);

    // default encoding used when reading/writing files
    QString encoding();
    void setEncoding(const QString & v);

    // Force using a particular line end type (win, linux, mac) when saving text files
    QString forceLineEnd();
    void setForceLineEnd(const QString & v);

    // Extractor. Controls the method used to produce database object extracts
    // as well as extraction settings (which information should be extracted).
    bool extractorUseDbmsMetadata();
    void setExtractorUseDbmsMetadata(bool v);

    bool extractorIncludeSotrage();
    void setExtractorIncludeSotrage(bool v);

    bool extractorSkipOrgMonInformation();
    void setExtractorSkipOrgMonInformation(bool v);

    bool extractorSkipStorageExceptTablespaces();
    void setExtractorSkipStorageExceptTablespaces(bool v);

    bool extractorIncludeParallel();
    void setExtractorIncludeParallel(bool v);

    bool extractorIncludePartition();
    void setExtractorIncludePartition(bool v);

    bool extractorIncludeCode();
    void setExtractorIncludeCode(bool v);

    bool extractorIncludeHeader();
    void setExtractorIncludeHeader(bool v);

    bool extractorIncludePrompt();
    void setExtractorIncludePrompt(bool v);
    
    // Aplication location paths
    QString sharePath();
};

typedef Loki::SingletonHolder<toConfiguration> toConfigurationSingle;

#endif