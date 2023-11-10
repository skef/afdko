
// Generated from FeatParser.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  FeatParser : public antlr4::Parser {
public:
  enum {
    ANON = 1, ANON_v = 2, COMMENT = 3, WHITESPACE = 4, INCLUDE = 5, FEATURE = 6, 
    TABLE = 7, SCRIPT = 8, LANGUAGE = 9, LANGSYS = 10, SUBTABLE = 11, LOOKUP = 12, 
    LOOKUPFLAG = 13, NOTDEF = 14, RIGHT_TO_LEFT = 15, IGNORE_BASE_GLYPHS = 16, 
    IGNORE_LIGATURES = 17, IGNORE_MARKS = 18, USE_MARK_FILTERING_SET = 19, 
    MARK_ATTACHMENT_TYPE = 20, EXCLUDE_DFLT = 21, INCLUDE_DFLT = 22, EXCLUDE_dflt = 23, 
    INCLUDE_dflt = 24, USE_EXTENSION = 25, BEGINVALUE = 26, ENDVALUE = 27, 
    ENUMERATE = 28, ENUMERATE_v = 29, EXCEPT = 30, IGNORE = 31, SUBSTITUTE = 32, 
    SUBSTITUTE_v = 33, REVERSE = 34, REVERSE_v = 35, BY = 36, FROM = 37, 
    POSITION = 38, POSITION_v = 39, PARAMETERS = 40, FEATURE_NAMES = 41, 
    CV_PARAMETERS = 42, CV_UI_LABEL = 43, CV_TOOLTIP = 44, CV_SAMPLE_TEXT = 45, 
    CV_PARAM_LABEL = 46, CV_CHARACTER = 47, SIZEMENUNAME = 48, CONTOURPOINT = 49, 
    ANCHOR = 50, ANCHOR_DEF = 51, VALUE_RECORD_DEF = 52, LOCATION_DEF = 53, 
    MARK = 54, MARK_CLASS = 55, CURSIVE = 56, MARKBASE = 57, MARKLIG = 58, 
    MARKLIG_v = 59, LIG_COMPONENT = 60, KNULL = 61, BASE = 62, HA_BTL = 63, 
    VA_BTL = 64, HA_BSL = 65, VA_BSL = 66, GDEF = 67, GLYPH_CLASS_DEF = 68, 
    ATTACH = 69, LIG_CARET_BY_POS = 70, LIG_CARET_BY_IDX = 71, HEAD = 72, 
    FONT_REVISION = 73, HHEA = 74, ASCENDER = 75, DESCENDER = 76, LINE_GAP = 77, 
    CARET_OFFSET = 78, NAME = 79, NAMEID = 80, OS_2 = 81, FS_TYPE = 82, 
    FS_TYPE_v = 83, OS2_LOWER_OP_SIZE = 84, OS2_UPPER_OP_SIZE = 85, PANOSE = 86, 
    TYPO_ASCENDER = 87, TYPO_DESCENDER = 88, TYPO_LINE_GAP = 89, WIN_ASCENT = 90, 
    WIN_DESCENT = 91, X_HEIGHT = 92, CAP_HEIGHT = 93, WEIGHT_CLASS = 94, 
    WIDTH_CLASS = 95, VENDOR = 96, UNICODE_RANGE = 97, CODE_PAGE_RANGE = 98, 
    FAMILY_CLASS = 99, STAT = 100, ELIDED_FALLBACK_NAME = 101, ELIDED_FALLBACK_NAME_ID = 102, 
    DESIGN_AXIS = 103, AXIS_VALUE = 104, FLAG = 105, LOCATION = 106, AXIS_EAVN = 107, 
    AXIS_OSFA = 108, VHEA = 109, VERT_TYPO_ASCENDER = 110, VERT_TYPO_DESCENDER = 111, 
    VERT_TYPO_LINE_GAP = 112, VMTX = 113, VERT_ORIGIN_Y = 114, VERT_ADVANCE_Y = 115, 
    LCBRACE = 116, RCBRACE = 117, LBRACKET = 118, RBRACKET = 119, LPAREN = 120, 
    RPAREN = 121, HYPHEN = 122, SEMI = 123, EQUALS = 124, MARKER = 125, 
    COMMA = 126, COLON = 127, QUOTE = 128, GCLASS = 129, AXISUNIT = 130, 
    CID = 131, ESCGNAME = 132, NAMELABEL = 133, EXTNAME = 134, POINTNUM = 135, 
    NUMEXT = 136, NUMOCT = 137, NUM = 138, CATCHTAG = 139, A_WHITESPACE = 140, 
    A_LABEL = 141, A_LBRACE = 142, A_CLOSE = 143, A_LINE = 144, I_WHITESPACE = 145, 
    I_RPAREN = 146, IFILE = 147, I_LPAREN = 148, STRVAL = 149, EQUOTE = 150
  };

  enum {
    RuleFile = 0, RuleTopLevelStatement = 1, RuleInclude = 2, RuleGlyphClassAssign = 3, 
    RuleLangsysAssign = 4, RuleMark_statement = 5, RuleAnchorDef = 6, RuleValueRecordDef = 7, 
    RuleLocationDef = 8, RuleFeatureBlock = 9, RuleTableBlock = 10, RuleAnonBlock = 11, 
    RuleLookupBlockTopLevel = 12, RuleFeatureStatement = 13, RuleLookupBlockOrUse = 14, 
    RuleCvParameterBlock = 15, RuleCvParameterStatement = 16, RuleCvParameter = 17, 
    RuleStatement = 18, RuleFeatureUse = 19, RuleScriptAssign = 20, RuleLangAssign = 21, 
    RuleLookupflagAssign = 22, RuleLookupflagElement = 23, RuleIgnoreSubOrPos = 24, 
    RuleSubstitute = 25, RulePosition = 26, RuleValuePattern = 27, RuleValueRecord = 28, 
    RuleValueLiteral = 29, RuleParenLocationValue = 30, RuleLocationValueLiteral = 31, 
    RuleLocationMultiValueLiteral = 32, RuleLocationSpecifier = 33, RuleLocationLiteral = 34, 
    RuleAxisLocationLiteral = 35, RuleCursiveElement = 36, RuleBaseToMarkElement = 37, 
    RuleLigatureMarkElement = 38, RuleParameters = 39, RuleSizemenuname = 40, 
    RuleFeatureNames = 41, RuleSubtable = 42, RuleTable_BASE = 43, RuleBaseStatement = 44, 
    RuleAxisTags = 45, RuleAxisScripts = 46, RuleBaseScript = 47, RuleTable_GDEF = 48, 
    RuleGdefStatement = 49, RuleGdefGlyphClass = 50, RuleGdefAttach = 51, 
    RuleGdefLigCaretPos = 52, RuleGdefLigCaretIndex = 53, RuleTable_head = 54, 
    RuleHeadStatement = 55, RuleHead = 56, RuleTable_hhea = 57, RuleHheaStatement = 58, 
    RuleHhea = 59, RuleTable_vhea = 60, RuleVheaStatement = 61, RuleVhea = 62, 
    RuleTable_name = 63, RuleNameStatement = 64, RuleNameID = 65, RuleTable_OS_2 = 66, 
    RuleOs_2Statement = 67, RuleOs_2 = 68, RuleTable_STAT = 69, RuleStatStatement = 70, 
    RuleDesignAxis = 71, RuleAxisValue = 72, RuleAxisValueStatement = 73, 
    RuleAxisValueLocation = 74, RuleAxisValueFlags = 75, RuleElidedFallbackName = 76, 
    RuleNameEntryStatement = 77, RuleElidedFallbackNameID = 78, RuleNameEntry = 79, 
    RuleTable_vmtx = 80, RuleVmtxStatement = 81, RuleVmtx = 82, RuleAnchor = 83, 
    RuleLookupPattern = 84, RuleLookupPatternElement = 85, RulePattern = 86, 
    RulePatternElement = 87, RuleGlyphClassOptional = 88, RuleGlyphClass = 89, 
    RuleGcLiteral = 90, RuleGcLiteralElement = 91, RuleGlyph = 92, RuleGlyphName = 93, 
    RuleLabel = 94, RuleTag = 95, RuleFixedNum = 96, RuleGenNum = 97, RuleFeatureFile = 98, 
    RuleStatementFile = 99, RuleCvStatementFile = 100, RuleBaseFile = 101, 
    RuleHeadFile = 102, RuleHheaFile = 103, RuleVheaFile = 104, RuleGdefFile = 105, 
    RuleNameFile = 106, RuleVmtxFile = 107, RuleOs_2File = 108, RuleStatFile = 109, 
    RuleAxisValueFile = 110, RuleNameEntryFile = 111, RuleSubtok = 112, 
    RuleRevtok = 113, RuleAnontok = 114, RuleEnumtok = 115, RulePostok = 116, 
    RuleMarkligtok = 117
  };

  explicit FeatParser(antlr4::TokenStream *input);

  FeatParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~FeatParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class FileContext;
  class TopLevelStatementContext;
  class IncludeContext;
  class GlyphClassAssignContext;
  class LangsysAssignContext;
  class Mark_statementContext;
  class AnchorDefContext;
  class ValueRecordDefContext;
  class LocationDefContext;
  class FeatureBlockContext;
  class TableBlockContext;
  class AnonBlockContext;
  class LookupBlockTopLevelContext;
  class FeatureStatementContext;
  class LookupBlockOrUseContext;
  class CvParameterBlockContext;
  class CvParameterStatementContext;
  class CvParameterContext;
  class StatementContext;
  class FeatureUseContext;
  class ScriptAssignContext;
  class LangAssignContext;
  class LookupflagAssignContext;
  class LookupflagElementContext;
  class IgnoreSubOrPosContext;
  class SubstituteContext;
  class PositionContext;
  class ValuePatternContext;
  class ValueRecordContext;
  class ValueLiteralContext;
  class ParenLocationValueContext;
  class LocationValueLiteralContext;
  class LocationMultiValueLiteralContext;
  class LocationSpecifierContext;
  class LocationLiteralContext;
  class AxisLocationLiteralContext;
  class CursiveElementContext;
  class BaseToMarkElementContext;
  class LigatureMarkElementContext;
  class ParametersContext;
  class SizemenunameContext;
  class FeatureNamesContext;
  class SubtableContext;
  class Table_BASEContext;
  class BaseStatementContext;
  class AxisTagsContext;
  class AxisScriptsContext;
  class BaseScriptContext;
  class Table_GDEFContext;
  class GdefStatementContext;
  class GdefGlyphClassContext;
  class GdefAttachContext;
  class GdefLigCaretPosContext;
  class GdefLigCaretIndexContext;
  class Table_headContext;
  class HeadStatementContext;
  class HeadContext;
  class Table_hheaContext;
  class HheaStatementContext;
  class HheaContext;
  class Table_vheaContext;
  class VheaStatementContext;
  class VheaContext;
  class Table_nameContext;
  class NameStatementContext;
  class NameIDContext;
  class Table_OS_2Context;
  class Os_2StatementContext;
  class Os_2Context;
  class Table_STATContext;
  class StatStatementContext;
  class DesignAxisContext;
  class AxisValueContext;
  class AxisValueStatementContext;
  class AxisValueLocationContext;
  class AxisValueFlagsContext;
  class ElidedFallbackNameContext;
  class NameEntryStatementContext;
  class ElidedFallbackNameIDContext;
  class NameEntryContext;
  class Table_vmtxContext;
  class VmtxStatementContext;
  class VmtxContext;
  class AnchorContext;
  class LookupPatternContext;
  class LookupPatternElementContext;
  class PatternContext;
  class PatternElementContext;
  class GlyphClassOptionalContext;
  class GlyphClassContext;
  class GcLiteralContext;
  class GcLiteralElementContext;
  class GlyphContext;
  class GlyphNameContext;
  class LabelContext;
  class TagContext;
  class FixedNumContext;
  class GenNumContext;
  class FeatureFileContext;
  class StatementFileContext;
  class CvStatementFileContext;
  class BaseFileContext;
  class HeadFileContext;
  class HheaFileContext;
  class VheaFileContext;
  class GdefFileContext;
  class NameFileContext;
  class VmtxFileContext;
  class Os_2FileContext;
  class StatFileContext;
  class AxisValueFileContext;
  class NameEntryFileContext;
  class SubtokContext;
  class RevtokContext;
  class AnontokContext;
  class EnumtokContext;
  class PostokContext;
  class MarkligtokContext; 

  class  FileContext : public antlr4::ParserRuleContext {
  public:
    FileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<TopLevelStatementContext *> topLevelStatement();
    TopLevelStatementContext* topLevelStatement(size_t i);
    std::vector<FeatureBlockContext *> featureBlock();
    FeatureBlockContext* featureBlock(size_t i);
    std::vector<TableBlockContext *> tableBlock();
    TableBlockContext* tableBlock(size_t i);
    std::vector<AnonBlockContext *> anonBlock();
    AnonBlockContext* anonBlock(size_t i);
    std::vector<LookupBlockTopLevelContext *> lookupBlockTopLevel();
    LookupBlockTopLevelContext* lookupBlockTopLevel(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FileContext* file();

  class  TopLevelStatementContext : public antlr4::ParserRuleContext {
  public:
    TopLevelStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SEMI();
    IncludeContext *include();
    GlyphClassAssignContext *glyphClassAssign();
    LangsysAssignContext *langsysAssign();
    Mark_statementContext *mark_statement();
    AnchorDefContext *anchorDef();
    ValueRecordDefContext *valueRecordDef();
    LocationDefContext *locationDef();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TopLevelStatementContext* topLevelStatement();

  class  IncludeContext : public antlr4::ParserRuleContext {
  public:
    IncludeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INCLUDE();
    antlr4::tree::TerminalNode *I_RPAREN();
    antlr4::tree::TerminalNode *IFILE();
    antlr4::tree::TerminalNode *I_LPAREN();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IncludeContext* include();

  class  GlyphClassAssignContext : public antlr4::ParserRuleContext {
  public:
    GlyphClassAssignContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *GCLASS();
    antlr4::tree::TerminalNode *EQUALS();
    GlyphClassContext *glyphClass();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GlyphClassAssignContext* glyphClassAssign();

  class  LangsysAssignContext : public antlr4::ParserRuleContext {
  public:
    FeatParser::TagContext *script = nullptr;
    FeatParser::TagContext *lang = nullptr;
    LangsysAssignContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LANGSYS();
    std::vector<TagContext *> tag();
    TagContext* tag(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LangsysAssignContext* langsysAssign();

  class  Mark_statementContext : public antlr4::ParserRuleContext {
  public:
    Mark_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *MARK_CLASS();
    AnchorContext *anchor();
    antlr4::tree::TerminalNode *GCLASS();
    GlyphContext *glyph();
    GlyphClassContext *glyphClass();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Mark_statementContext* mark_statement();

  class  AnchorDefContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *xval = nullptr;
    antlr4::Token *yval = nullptr;
    antlr4::Token *cp = nullptr;
    FeatParser::LabelContext *name = nullptr;
    AnchorDefContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ANCHOR_DEF();
    std::vector<antlr4::tree::TerminalNode *> NUM();
    antlr4::tree::TerminalNode* NUM(size_t i);
    LabelContext *label();
    antlr4::tree::TerminalNode *CONTOURPOINT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AnchorDefContext* anchorDef();

  class  ValueRecordDefContext : public antlr4::ParserRuleContext {
  public:
    ValueRecordDefContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VALUE_RECORD_DEF();
    ValueLiteralContext *valueLiteral();
    LabelContext *label();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ValueRecordDefContext* valueRecordDef();

  class  LocationDefContext : public antlr4::ParserRuleContext {
  public:
    LocationDefContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LOCATION_DEF();
    LocationLiteralContext *locationLiteral();
    LabelContext *label();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LocationDefContext* locationDef();

  class  FeatureBlockContext : public antlr4::ParserRuleContext {
  public:
    FeatParser::TagContext *starttag = nullptr;
    FeatParser::TagContext *endtag = nullptr;
    FeatureBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FEATURE();
    antlr4::tree::TerminalNode *LCBRACE();
    antlr4::tree::TerminalNode *RCBRACE();
    antlr4::tree::TerminalNode *SEMI();
    std::vector<TagContext *> tag();
    TagContext* tag(size_t i);
    antlr4::tree::TerminalNode *USE_EXTENSION();
    std::vector<FeatureStatementContext *> featureStatement();
    FeatureStatementContext* featureStatement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FeatureBlockContext* featureBlock();

  class  TableBlockContext : public antlr4::ParserRuleContext {
  public:
    TableBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TABLE();
    Table_BASEContext *table_BASE();
    Table_GDEFContext *table_GDEF();
    Table_headContext *table_head();
    Table_hheaContext *table_hhea();
    Table_vheaContext *table_vhea();
    Table_nameContext *table_name();
    Table_OS_2Context *table_OS_2();
    Table_STATContext *table_STAT();
    Table_vmtxContext *table_vmtx();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TableBlockContext* tableBlock();

  class  AnonBlockContext : public antlr4::ParserRuleContext {
  public:
    AnonBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AnontokContext *anontok();
    antlr4::tree::TerminalNode *A_LABEL();
    antlr4::tree::TerminalNode *A_LBRACE();
    antlr4::tree::TerminalNode *A_CLOSE();
    std::vector<antlr4::tree::TerminalNode *> A_LINE();
    antlr4::tree::TerminalNode* A_LINE(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AnonBlockContext* anonBlock();

  class  LookupBlockTopLevelContext : public antlr4::ParserRuleContext {
  public:
    FeatParser::LabelContext *startlabel = nullptr;
    FeatParser::LabelContext *endlabel = nullptr;
    LookupBlockTopLevelContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LOOKUP();
    antlr4::tree::TerminalNode *LCBRACE();
    antlr4::tree::TerminalNode *RCBRACE();
    antlr4::tree::TerminalNode *SEMI();
    std::vector<LabelContext *> label();
    LabelContext* label(size_t i);
    antlr4::tree::TerminalNode *USE_EXTENSION();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LookupBlockTopLevelContext* lookupBlockTopLevel();

  class  FeatureStatementContext : public antlr4::ParserRuleContext {
  public:
    FeatureStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StatementContext *statement();
    LookupBlockOrUseContext *lookupBlockOrUse();
    CvParameterBlockContext *cvParameterBlock();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FeatureStatementContext* featureStatement();

  class  LookupBlockOrUseContext : public antlr4::ParserRuleContext {
  public:
    FeatParser::LabelContext *startlabel = nullptr;
    FeatParser::LabelContext *endlabel = nullptr;
    LookupBlockOrUseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LOOKUP();
    antlr4::tree::TerminalNode *SEMI();
    std::vector<LabelContext *> label();
    LabelContext* label(size_t i);
    antlr4::tree::TerminalNode *LCBRACE();
    antlr4::tree::TerminalNode *RCBRACE();
    antlr4::tree::TerminalNode *USE_EXTENSION();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LookupBlockOrUseContext* lookupBlockOrUse();

  class  CvParameterBlockContext : public antlr4::ParserRuleContext {
  public:
    CvParameterBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CV_PARAMETERS();
    antlr4::tree::TerminalNode *LCBRACE();
    antlr4::tree::TerminalNode *RCBRACE();
    antlr4::tree::TerminalNode *SEMI();
    std::vector<CvParameterStatementContext *> cvParameterStatement();
    CvParameterStatementContext* cvParameterStatement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CvParameterBlockContext* cvParameterBlock();

  class  CvParameterStatementContext : public antlr4::ParserRuleContext {
  public:
    CvParameterStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SEMI();
    CvParameterContext *cvParameter();
    IncludeContext *include();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CvParameterStatementContext* cvParameterStatement();

  class  CvParameterContext : public antlr4::ParserRuleContext {
  public:
    CvParameterContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LCBRACE();
    antlr4::tree::TerminalNode *RCBRACE();
    antlr4::tree::TerminalNode *CV_UI_LABEL();
    antlr4::tree::TerminalNode *CV_TOOLTIP();
    antlr4::tree::TerminalNode *CV_SAMPLE_TEXT();
    antlr4::tree::TerminalNode *CV_PARAM_LABEL();
    std::vector<NameEntryStatementContext *> nameEntryStatement();
    NameEntryStatementContext* nameEntryStatement(size_t i);
    antlr4::tree::TerminalNode *CV_CHARACTER();
    GenNumContext *genNum();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CvParameterContext* cvParameter();

  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SEMI();
    FeatureUseContext *featureUse();
    ScriptAssignContext *scriptAssign();
    LangAssignContext *langAssign();
    LookupflagAssignContext *lookupflagAssign();
    GlyphClassAssignContext *glyphClassAssign();
    IgnoreSubOrPosContext *ignoreSubOrPos();
    SubstituteContext *substitute();
    Mark_statementContext *mark_statement();
    PositionContext *position();
    ParametersContext *parameters();
    SizemenunameContext *sizemenuname();
    FeatureNamesContext *featureNames();
    SubtableContext *subtable();
    IncludeContext *include();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementContext* statement();

  class  FeatureUseContext : public antlr4::ParserRuleContext {
  public:
    FeatureUseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FEATURE();
    TagContext *tag();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FeatureUseContext* featureUse();

  class  ScriptAssignContext : public antlr4::ParserRuleContext {
  public:
    ScriptAssignContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SCRIPT();
    TagContext *tag();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ScriptAssignContext* scriptAssign();

  class  LangAssignContext : public antlr4::ParserRuleContext {
  public:
    LangAssignContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LANGUAGE();
    TagContext *tag();
    antlr4::tree::TerminalNode *EXCLUDE_DFLT();
    antlr4::tree::TerminalNode *INCLUDE_DFLT();
    antlr4::tree::TerminalNode *EXCLUDE_dflt();
    antlr4::tree::TerminalNode *INCLUDE_dflt();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LangAssignContext* langAssign();

  class  LookupflagAssignContext : public antlr4::ParserRuleContext {
  public:
    LookupflagAssignContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LOOKUPFLAG();
    antlr4::tree::TerminalNode *NUM();
    std::vector<LookupflagElementContext *> lookupflagElement();
    LookupflagElementContext* lookupflagElement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LookupflagAssignContext* lookupflagAssign();

  class  LookupflagElementContext : public antlr4::ParserRuleContext {
  public:
    LookupflagElementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *RIGHT_TO_LEFT();
    antlr4::tree::TerminalNode *IGNORE_BASE_GLYPHS();
    antlr4::tree::TerminalNode *IGNORE_LIGATURES();
    antlr4::tree::TerminalNode *IGNORE_MARKS();
    antlr4::tree::TerminalNode *MARK_ATTACHMENT_TYPE();
    GlyphClassContext *glyphClass();
    antlr4::tree::TerminalNode *USE_MARK_FILTERING_SET();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LookupflagElementContext* lookupflagElement();

  class  IgnoreSubOrPosContext : public antlr4::ParserRuleContext {
  public:
    IgnoreSubOrPosContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IGNORE();
    std::vector<LookupPatternContext *> lookupPattern();
    LookupPatternContext* lookupPattern(size_t i);
    SubtokContext *subtok();
    RevtokContext *revtok();
    PostokContext *postok();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IgnoreSubOrPosContext* ignoreSubOrPos();

  class  SubstituteContext : public antlr4::ParserRuleContext {
  public:
    FeatParser::LookupPatternContext *startpat = nullptr;
    FeatParser::LookupPatternContext *endpat = nullptr;
    SubstituteContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    RevtokContext *revtok();
    SubtokContext *subtok();
    antlr4::tree::TerminalNode *EXCEPT();
    std::vector<LookupPatternContext *> lookupPattern();
    LookupPatternContext* lookupPattern(size_t i);
    antlr4::tree::TerminalNode *BY();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);
    antlr4::tree::TerminalNode *FROM();
    antlr4::tree::TerminalNode *KNULL();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SubstituteContext* substitute();

  class  PositionContext : public antlr4::ParserRuleContext {
  public:
    FeatParser::PatternContext *startpat = nullptr;
    FeatParser::PatternContext *endpat = nullptr;
    FeatParser::PatternContext *midpat = nullptr;
    PositionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PostokContext *postok();
    EnumtokContext *enumtok();
    std::vector<PatternContext *> pattern();
    PatternContext* pattern(size_t i);
    ValueRecordContext *valueRecord();
    antlr4::tree::TerminalNode *CURSIVE();
    CursiveElementContext *cursiveElement();
    antlr4::tree::TerminalNode *MARKBASE();
    MarkligtokContext *markligtok();
    antlr4::tree::TerminalNode *MARK();
    std::vector<ValuePatternContext *> valuePattern();
    ValuePatternContext* valuePattern(size_t i);
    std::vector<antlr4::tree::TerminalNode *> LOOKUP();
    antlr4::tree::TerminalNode* LOOKUP(size_t i);
    std::vector<LabelContext *> label();
    LabelContext* label(size_t i);
    std::vector<LookupPatternElementContext *> lookupPatternElement();
    LookupPatternElementContext* lookupPatternElement(size_t i);
    std::vector<BaseToMarkElementContext *> baseToMarkElement();
    BaseToMarkElementContext* baseToMarkElement(size_t i);
    std::vector<LigatureMarkElementContext *> ligatureMarkElement();
    LigatureMarkElementContext* ligatureMarkElement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PositionContext* position();

  class  ValuePatternContext : public antlr4::ParserRuleContext {
  public:
    ValuePatternContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PatternElementContext *patternElement();
    ValueRecordContext *valueRecord();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ValuePatternContext* valuePattern();

  class  ValueRecordContext : public antlr4::ParserRuleContext {
  public:
    FeatParser::LabelContext *valuename = nullptr;
    ValueRecordContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *BEGINVALUE();
    antlr4::tree::TerminalNode *ENDVALUE();
    LabelContext *label();
    ValueLiteralContext *valueLiteral();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ValueRecordContext* valueRecord();

  class  ValueLiteralContext : public antlr4::ParserRuleContext {
  public:
    ValueLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> NUM();
    antlr4::tree::TerminalNode* NUM(size_t i);
    antlr4::tree::TerminalNode *BEGINVALUE();
    antlr4::tree::TerminalNode *ENDVALUE();
    std::vector<ParenLocationValueContext *> parenLocationValue();
    ParenLocationValueContext* parenLocationValue(size_t i);
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    std::vector<LocationMultiValueLiteralContext *> locationMultiValueLiteral();
    LocationMultiValueLiteralContext* locationMultiValueLiteral(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ValueLiteralContext* valueLiteral();

  class  ParenLocationValueContext : public antlr4::ParserRuleContext {
  public:
    ParenLocationValueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    std::vector<LocationValueLiteralContext *> locationValueLiteral();
    LocationValueLiteralContext* locationValueLiteral(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParenLocationValueContext* parenLocationValue();

  class  LocationValueLiteralContext : public antlr4::ParserRuleContext {
  public:
    LocationValueLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LocationSpecifierContext *locationSpecifier();
    antlr4::tree::TerminalNode *COLON();
    antlr4::tree::TerminalNode *NUM();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LocationValueLiteralContext* locationValueLiteral();

  class  LocationMultiValueLiteralContext : public antlr4::ParserRuleContext {
  public:
    LocationMultiValueLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LocationSpecifierContext *locationSpecifier();
    antlr4::tree::TerminalNode *COLON();
    antlr4::tree::TerminalNode *BEGINVALUE();
    std::vector<antlr4::tree::TerminalNode *> NUM();
    antlr4::tree::TerminalNode* NUM(size_t i);
    antlr4::tree::TerminalNode *ENDVALUE();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LocationMultiValueLiteralContext* locationMultiValueLiteral();

  class  LocationSpecifierContext : public antlr4::ParserRuleContext {
  public:
    LocationSpecifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LocationLiteralContext *locationLiteral();
    LabelContext *label();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LocationSpecifierContext* locationSpecifier();

  class  LocationLiteralContext : public antlr4::ParserRuleContext {
  public:
    LocationLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<AxisLocationLiteralContext *> axisLocationLiteral();
    AxisLocationLiteralContext* axisLocationLiteral(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LocationLiteralContext* locationLiteral();

  class  AxisLocationLiteralContext : public antlr4::ParserRuleContext {
  public:
    AxisLocationLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TagContext *tag();
    antlr4::tree::TerminalNode *EQUALS();
    FixedNumContext *fixedNum();
    antlr4::tree::TerminalNode *AXISUNIT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AxisLocationLiteralContext* axisLocationLiteral();

  class  CursiveElementContext : public antlr4::ParserRuleContext {
  public:
    CursiveElementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PatternElementContext *patternElement();
    std::vector<AnchorContext *> anchor();
    AnchorContext* anchor(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CursiveElementContext* cursiveElement();

  class  BaseToMarkElementContext : public antlr4::ParserRuleContext {
  public:
    BaseToMarkElementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AnchorContext *anchor();
    antlr4::tree::TerminalNode *MARK();
    antlr4::tree::TerminalNode *GCLASS();
    antlr4::tree::TerminalNode *MARKER();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BaseToMarkElementContext* baseToMarkElement();

  class  LigatureMarkElementContext : public antlr4::ParserRuleContext {
  public:
    LigatureMarkElementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AnchorContext *anchor();
    antlr4::tree::TerminalNode *MARK();
    antlr4::tree::TerminalNode *GCLASS();
    antlr4::tree::TerminalNode *LIG_COMPONENT();
    antlr4::tree::TerminalNode *MARKER();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LigatureMarkElementContext* ligatureMarkElement();

  class  ParametersContext : public antlr4::ParserRuleContext {
  public:
    ParametersContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *PARAMETERS();
    std::vector<FixedNumContext *> fixedNum();
    FixedNumContext* fixedNum(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParametersContext* parameters();

  class  SizemenunameContext : public antlr4::ParserRuleContext {
  public:
    SizemenunameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SIZEMENUNAME();
    antlr4::tree::TerminalNode *QUOTE();
    antlr4::tree::TerminalNode *STRVAL();
    antlr4::tree::TerminalNode *EQUOTE();
    std::vector<GenNumContext *> genNum();
    GenNumContext* genNum(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SizemenunameContext* sizemenuname();

  class  FeatureNamesContext : public antlr4::ParserRuleContext {
  public:
    FeatureNamesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FEATURE_NAMES();
    antlr4::tree::TerminalNode *LCBRACE();
    antlr4::tree::TerminalNode *RCBRACE();
    std::vector<NameEntryStatementContext *> nameEntryStatement();
    NameEntryStatementContext* nameEntryStatement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FeatureNamesContext* featureNames();

  class  SubtableContext : public antlr4::ParserRuleContext {
  public:
    SubtableContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SUBTABLE();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SubtableContext* subtable();

  class  Table_BASEContext : public antlr4::ParserRuleContext {
  public:
    Table_BASEContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> BASE();
    antlr4::tree::TerminalNode* BASE(size_t i);
    antlr4::tree::TerminalNode *LCBRACE();
    antlr4::tree::TerminalNode *RCBRACE();
    antlr4::tree::TerminalNode *SEMI();
    std::vector<BaseStatementContext *> baseStatement();
    BaseStatementContext* baseStatement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Table_BASEContext* table_BASE();

  class  BaseStatementContext : public antlr4::ParserRuleContext {
  public:
    BaseStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SEMI();
    AxisTagsContext *axisTags();
    AxisScriptsContext *axisScripts();
    IncludeContext *include();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BaseStatementContext* baseStatement();

  class  AxisTagsContext : public antlr4::ParserRuleContext {
  public:
    AxisTagsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *HA_BTL();
    antlr4::tree::TerminalNode *VA_BTL();
    std::vector<TagContext *> tag();
    TagContext* tag(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AxisTagsContext* axisTags();

  class  AxisScriptsContext : public antlr4::ParserRuleContext {
  public:
    AxisScriptsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<BaseScriptContext *> baseScript();
    BaseScriptContext* baseScript(size_t i);
    antlr4::tree::TerminalNode *HA_BSL();
    antlr4::tree::TerminalNode *VA_BSL();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AxisScriptsContext* axisScripts();

  class  BaseScriptContext : public antlr4::ParserRuleContext {
  public:
    FeatParser::TagContext *script = nullptr;
    FeatParser::TagContext *db = nullptr;
    BaseScriptContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<TagContext *> tag();
    TagContext* tag(size_t i);
    std::vector<antlr4::tree::TerminalNode *> NUM();
    antlr4::tree::TerminalNode* NUM(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BaseScriptContext* baseScript();

  class  Table_GDEFContext : public antlr4::ParserRuleContext {
  public:
    Table_GDEFContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> GDEF();
    antlr4::tree::TerminalNode* GDEF(size_t i);
    antlr4::tree::TerminalNode *LCBRACE();
    antlr4::tree::TerminalNode *RCBRACE();
    antlr4::tree::TerminalNode *SEMI();
    std::vector<GdefStatementContext *> gdefStatement();
    GdefStatementContext* gdefStatement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Table_GDEFContext* table_GDEF();

  class  GdefStatementContext : public antlr4::ParserRuleContext {
  public:
    GdefStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SEMI();
    GdefGlyphClassContext *gdefGlyphClass();
    GdefAttachContext *gdefAttach();
    GdefLigCaretPosContext *gdefLigCaretPos();
    GdefLigCaretIndexContext *gdefLigCaretIndex();
    IncludeContext *include();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GdefStatementContext* gdefStatement();

  class  GdefGlyphClassContext : public antlr4::ParserRuleContext {
  public:
    GdefGlyphClassContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *GLYPH_CLASS_DEF();
    std::vector<GlyphClassOptionalContext *> glyphClassOptional();
    GlyphClassOptionalContext* glyphClassOptional(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GdefGlyphClassContext* gdefGlyphClass();

  class  GdefAttachContext : public antlr4::ParserRuleContext {
  public:
    GdefAttachContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ATTACH();
    LookupPatternContext *lookupPattern();
    std::vector<antlr4::tree::TerminalNode *> NUM();
    antlr4::tree::TerminalNode* NUM(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GdefAttachContext* gdefAttach();

  class  GdefLigCaretPosContext : public antlr4::ParserRuleContext {
  public:
    GdefLigCaretPosContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LIG_CARET_BY_POS();
    LookupPatternContext *lookupPattern();
    std::vector<antlr4::tree::TerminalNode *> NUM();
    antlr4::tree::TerminalNode* NUM(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GdefLigCaretPosContext* gdefLigCaretPos();

  class  GdefLigCaretIndexContext : public antlr4::ParserRuleContext {
  public:
    GdefLigCaretIndexContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LIG_CARET_BY_IDX();
    LookupPatternContext *lookupPattern();
    std::vector<antlr4::tree::TerminalNode *> NUM();
    antlr4::tree::TerminalNode* NUM(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GdefLigCaretIndexContext* gdefLigCaretIndex();

  class  Table_headContext : public antlr4::ParserRuleContext {
  public:
    Table_headContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> HEAD();
    antlr4::tree::TerminalNode* HEAD(size_t i);
    antlr4::tree::TerminalNode *LCBRACE();
    antlr4::tree::TerminalNode *RCBRACE();
    antlr4::tree::TerminalNode *SEMI();
    std::vector<HeadStatementContext *> headStatement();
    HeadStatementContext* headStatement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Table_headContext* table_head();

  class  HeadStatementContext : public antlr4::ParserRuleContext {
  public:
    HeadStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SEMI();
    HeadContext *head();
    IncludeContext *include();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  HeadStatementContext* headStatement();

  class  HeadContext : public antlr4::ParserRuleContext {
  public:
    HeadContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FONT_REVISION();
    antlr4::tree::TerminalNode *POINTNUM();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  HeadContext* head();

  class  Table_hheaContext : public antlr4::ParserRuleContext {
  public:
    Table_hheaContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> HHEA();
    antlr4::tree::TerminalNode* HHEA(size_t i);
    antlr4::tree::TerminalNode *LCBRACE();
    antlr4::tree::TerminalNode *RCBRACE();
    antlr4::tree::TerminalNode *SEMI();
    std::vector<HheaStatementContext *> hheaStatement();
    HheaStatementContext* hheaStatement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Table_hheaContext* table_hhea();

  class  HheaStatementContext : public antlr4::ParserRuleContext {
  public:
    HheaStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SEMI();
    HheaContext *hhea();
    IncludeContext *include();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  HheaStatementContext* hheaStatement();

  class  HheaContext : public antlr4::ParserRuleContext {
  public:
    HheaContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NUM();
    antlr4::tree::TerminalNode *CARET_OFFSET();
    antlr4::tree::TerminalNode *ASCENDER();
    antlr4::tree::TerminalNode *DESCENDER();
    antlr4::tree::TerminalNode *LINE_GAP();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  HheaContext* hhea();

  class  Table_vheaContext : public antlr4::ParserRuleContext {
  public:
    Table_vheaContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> VHEA();
    antlr4::tree::TerminalNode* VHEA(size_t i);
    antlr4::tree::TerminalNode *LCBRACE();
    antlr4::tree::TerminalNode *RCBRACE();
    antlr4::tree::TerminalNode *SEMI();
    std::vector<VheaStatementContext *> vheaStatement();
    VheaStatementContext* vheaStatement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Table_vheaContext* table_vhea();

  class  VheaStatementContext : public antlr4::ParserRuleContext {
  public:
    VheaStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SEMI();
    VheaContext *vhea();
    IncludeContext *include();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VheaStatementContext* vheaStatement();

  class  VheaContext : public antlr4::ParserRuleContext {
  public:
    VheaContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NUM();
    antlr4::tree::TerminalNode *VERT_TYPO_ASCENDER();
    antlr4::tree::TerminalNode *VERT_TYPO_DESCENDER();
    antlr4::tree::TerminalNode *VERT_TYPO_LINE_GAP();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VheaContext* vhea();

  class  Table_nameContext : public antlr4::ParserRuleContext {
  public:
    Table_nameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> NAME();
    antlr4::tree::TerminalNode* NAME(size_t i);
    antlr4::tree::TerminalNode *LCBRACE();
    antlr4::tree::TerminalNode *RCBRACE();
    antlr4::tree::TerminalNode *SEMI();
    std::vector<NameStatementContext *> nameStatement();
    NameStatementContext* nameStatement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Table_nameContext* table_name();

  class  NameStatementContext : public antlr4::ParserRuleContext {
  public:
    NameStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SEMI();
    NameIDContext *nameID();
    IncludeContext *include();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NameStatementContext* nameStatement();

  class  NameIDContext : public antlr4::ParserRuleContext {
  public:
    FeatParser::GenNumContext *id = nullptr;
    FeatParser::GenNumContext *plat = nullptr;
    FeatParser::GenNumContext *spec = nullptr;
    FeatParser::GenNumContext *lang = nullptr;
    NameIDContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NAMEID();
    antlr4::tree::TerminalNode *QUOTE();
    antlr4::tree::TerminalNode *STRVAL();
    antlr4::tree::TerminalNode *EQUOTE();
    std::vector<GenNumContext *> genNum();
    GenNumContext* genNum(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NameIDContext* nameID();

  class  Table_OS_2Context : public antlr4::ParserRuleContext {
  public:
    Table_OS_2Context(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> OS_2();
    antlr4::tree::TerminalNode* OS_2(size_t i);
    antlr4::tree::TerminalNode *LCBRACE();
    antlr4::tree::TerminalNode *RCBRACE();
    antlr4::tree::TerminalNode *SEMI();
    std::vector<Os_2StatementContext *> os_2Statement();
    Os_2StatementContext* os_2Statement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Table_OS_2Context* table_OS_2();

  class  Os_2StatementContext : public antlr4::ParserRuleContext {
  public:
    Os_2StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SEMI();
    Os_2Context *os_2();
    IncludeContext *include();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Os_2StatementContext* os_2Statement();

  class  Os_2Context : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *num = nullptr;
    antlr4::Token *unum = nullptr;
    FeatParser::GenNumContext *gnum = nullptr;
    Os_2Context(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TYPO_ASCENDER();
    antlr4::tree::TerminalNode *TYPO_DESCENDER();
    antlr4::tree::TerminalNode *TYPO_LINE_GAP();
    antlr4::tree::TerminalNode *WIN_ASCENT();
    antlr4::tree::TerminalNode *WIN_DESCENT();
    antlr4::tree::TerminalNode *X_HEIGHT();
    antlr4::tree::TerminalNode *CAP_HEIGHT();
    std::vector<antlr4::tree::TerminalNode *> NUM();
    antlr4::tree::TerminalNode* NUM(size_t i);
    antlr4::tree::TerminalNode *FS_TYPE();
    antlr4::tree::TerminalNode *FS_TYPE_v();
    antlr4::tree::TerminalNode *WEIGHT_CLASS();
    antlr4::tree::TerminalNode *WIDTH_CLASS();
    antlr4::tree::TerminalNode *OS2_LOWER_OP_SIZE();
    antlr4::tree::TerminalNode *OS2_UPPER_OP_SIZE();
    antlr4::tree::TerminalNode *FAMILY_CLASS();
    GenNumContext *genNum();
    antlr4::tree::TerminalNode *VENDOR();
    antlr4::tree::TerminalNode *QUOTE();
    antlr4::tree::TerminalNode *STRVAL();
    antlr4::tree::TerminalNode *EQUOTE();
    antlr4::tree::TerminalNode *PANOSE();
    antlr4::tree::TerminalNode *UNICODE_RANGE();
    antlr4::tree::TerminalNode *CODE_PAGE_RANGE();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Os_2Context* os_2();

  class  Table_STATContext : public antlr4::ParserRuleContext {
  public:
    Table_STATContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> STAT();
    antlr4::tree::TerminalNode* STAT(size_t i);
    antlr4::tree::TerminalNode *LCBRACE();
    antlr4::tree::TerminalNode *RCBRACE();
    antlr4::tree::TerminalNode *SEMI();
    std::vector<StatStatementContext *> statStatement();
    StatStatementContext* statStatement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Table_STATContext* table_STAT();

  class  StatStatementContext : public antlr4::ParserRuleContext {
  public:
    StatStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SEMI();
    DesignAxisContext *designAxis();
    AxisValueContext *axisValue();
    ElidedFallbackNameContext *elidedFallbackName();
    ElidedFallbackNameIDContext *elidedFallbackNameID();
    IncludeContext *include();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatStatementContext* statStatement();

  class  DesignAxisContext : public antlr4::ParserRuleContext {
  public:
    DesignAxisContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DESIGN_AXIS();
    TagContext *tag();
    antlr4::tree::TerminalNode *NUM();
    antlr4::tree::TerminalNode *LCBRACE();
    antlr4::tree::TerminalNode *RCBRACE();
    std::vector<NameEntryStatementContext *> nameEntryStatement();
    NameEntryStatementContext* nameEntryStatement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DesignAxisContext* designAxis();

  class  AxisValueContext : public antlr4::ParserRuleContext {
  public:
    AxisValueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *AXIS_VALUE();
    antlr4::tree::TerminalNode *LCBRACE();
    antlr4::tree::TerminalNode *RCBRACE();
    std::vector<AxisValueStatementContext *> axisValueStatement();
    AxisValueStatementContext* axisValueStatement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AxisValueContext* axisValue();

  class  AxisValueStatementContext : public antlr4::ParserRuleContext {
  public:
    AxisValueStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SEMI();
    NameEntryContext *nameEntry();
    AxisValueLocationContext *axisValueLocation();
    AxisValueFlagsContext *axisValueFlags();
    IncludeContext *include();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AxisValueStatementContext* axisValueStatement();

  class  AxisValueLocationContext : public antlr4::ParserRuleContext {
  public:
    AxisValueLocationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LOCATION();
    TagContext *tag();
    std::vector<FixedNumContext *> fixedNum();
    FixedNumContext* fixedNum(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AxisValueLocationContext* axisValueLocation();

  class  AxisValueFlagsContext : public antlr4::ParserRuleContext {
  public:
    AxisValueFlagsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FLAG();
    std::vector<antlr4::tree::TerminalNode *> AXIS_OSFA();
    antlr4::tree::TerminalNode* AXIS_OSFA(size_t i);
    std::vector<antlr4::tree::TerminalNode *> AXIS_EAVN();
    antlr4::tree::TerminalNode* AXIS_EAVN(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AxisValueFlagsContext* axisValueFlags();

  class  ElidedFallbackNameContext : public antlr4::ParserRuleContext {
  public:
    ElidedFallbackNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ELIDED_FALLBACK_NAME();
    antlr4::tree::TerminalNode *LCBRACE();
    antlr4::tree::TerminalNode *RCBRACE();
    std::vector<NameEntryStatementContext *> nameEntryStatement();
    NameEntryStatementContext* nameEntryStatement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ElidedFallbackNameContext* elidedFallbackName();

  class  NameEntryStatementContext : public antlr4::ParserRuleContext {
  public:
    NameEntryStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SEMI();
    NameEntryContext *nameEntry();
    IncludeContext *include();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NameEntryStatementContext* nameEntryStatement();

  class  ElidedFallbackNameIDContext : public antlr4::ParserRuleContext {
  public:
    ElidedFallbackNameIDContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ELIDED_FALLBACK_NAME_ID();
    GenNumContext *genNum();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ElidedFallbackNameIDContext* elidedFallbackNameID();

  class  NameEntryContext : public antlr4::ParserRuleContext {
  public:
    NameEntryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NAME();
    antlr4::tree::TerminalNode *QUOTE();
    antlr4::tree::TerminalNode *STRVAL();
    antlr4::tree::TerminalNode *EQUOTE();
    std::vector<GenNumContext *> genNum();
    GenNumContext* genNum(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NameEntryContext* nameEntry();

  class  Table_vmtxContext : public antlr4::ParserRuleContext {
  public:
    Table_vmtxContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> VMTX();
    antlr4::tree::TerminalNode* VMTX(size_t i);
    antlr4::tree::TerminalNode *LCBRACE();
    antlr4::tree::TerminalNode *RCBRACE();
    antlr4::tree::TerminalNode *SEMI();
    std::vector<VmtxStatementContext *> vmtxStatement();
    VmtxStatementContext* vmtxStatement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Table_vmtxContext* table_vmtx();

  class  VmtxStatementContext : public antlr4::ParserRuleContext {
  public:
    VmtxStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SEMI();
    VmtxContext *vmtx();
    IncludeContext *include();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VmtxStatementContext* vmtxStatement();

  class  VmtxContext : public antlr4::ParserRuleContext {
  public:
    VmtxContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    GlyphContext *glyph();
    antlr4::tree::TerminalNode *NUM();
    antlr4::tree::TerminalNode *VERT_ORIGIN_Y();
    antlr4::tree::TerminalNode *VERT_ADVANCE_Y();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VmtxContext* vmtx();

  class  AnchorContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *xval = nullptr;
    antlr4::Token *yval = nullptr;
    antlr4::Token *cp = nullptr;
    FeatParser::LabelContext *name = nullptr;
    AnchorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *BEGINVALUE();
    antlr4::tree::TerminalNode *ANCHOR();
    antlr4::tree::TerminalNode *ENDVALUE();
    antlr4::tree::TerminalNode *KNULL();
    LabelContext *label();
    std::vector<antlr4::tree::TerminalNode *> NUM();
    antlr4::tree::TerminalNode* NUM(size_t i);
    antlr4::tree::TerminalNode *CONTOURPOINT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AnchorContext* anchor();

  class  LookupPatternContext : public antlr4::ParserRuleContext {
  public:
    LookupPatternContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<LookupPatternElementContext *> lookupPatternElement();
    LookupPatternElementContext* lookupPatternElement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LookupPatternContext* lookupPattern();

  class  LookupPatternElementContext : public antlr4::ParserRuleContext {
  public:
    LookupPatternElementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PatternElementContext *patternElement();
    std::vector<antlr4::tree::TerminalNode *> LOOKUP();
    antlr4::tree::TerminalNode* LOOKUP(size_t i);
    std::vector<LabelContext *> label();
    LabelContext* label(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LookupPatternElementContext* lookupPatternElement();

  class  PatternContext : public antlr4::ParserRuleContext {
  public:
    PatternContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<PatternElementContext *> patternElement();
    PatternElementContext* patternElement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PatternContext* pattern();

  class  PatternElementContext : public antlr4::ParserRuleContext {
  public:
    PatternElementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    GlyphClassContext *glyphClass();
    GlyphContext *glyph();
    antlr4::tree::TerminalNode *MARKER();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PatternElementContext* patternElement();

  class  GlyphClassOptionalContext : public antlr4::ParserRuleContext {
  public:
    GlyphClassOptionalContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    GlyphClassContext *glyphClass();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GlyphClassOptionalContext* glyphClassOptional();

  class  GlyphClassContext : public antlr4::ParserRuleContext {
  public:
    GlyphClassContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *GCLASS();
    GcLiteralContext *gcLiteral();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GlyphClassContext* glyphClass();

  class  GcLiteralContext : public antlr4::ParserRuleContext {
  public:
    GcLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACKET();
    antlr4::tree::TerminalNode *RBRACKET();
    std::vector<GcLiteralElementContext *> gcLiteralElement();
    GcLiteralElementContext* gcLiteralElement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GcLiteralContext* gcLiteral();

  class  GcLiteralElementContext : public antlr4::ParserRuleContext {
  public:
    FeatParser::GlyphContext *startg = nullptr;
    FeatParser::GlyphContext *endg = nullptr;
    GcLiteralElementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<GlyphContext *> glyph();
    GlyphContext* glyph(size_t i);
    antlr4::tree::TerminalNode *HYPHEN();
    antlr4::tree::TerminalNode *GCLASS();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GcLiteralElementContext* gcLiteralElement();

  class  GlyphContext : public antlr4::ParserRuleContext {
  public:
    GlyphContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    GlyphNameContext *glyphName();
    antlr4::tree::TerminalNode *CID();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GlyphContext* glyph();

  class  GlyphNameContext : public antlr4::ParserRuleContext {
  public:
    GlyphNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ESCGNAME();
    antlr4::tree::TerminalNode *NAMELABEL();
    antlr4::tree::TerminalNode *EXTNAME();
    antlr4::tree::TerminalNode *AXISUNIT();
    antlr4::tree::TerminalNode *NOTDEF();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GlyphNameContext* glyphName();

  class  LabelContext : public antlr4::ParserRuleContext {
  public:
    LabelContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NAMELABEL();
    antlr4::tree::TerminalNode *MARK();
    antlr4::tree::TerminalNode *AXISUNIT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LabelContext* label();

  class  TagContext : public antlr4::ParserRuleContext {
  public:
    TagContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NAMELABEL();
    antlr4::tree::TerminalNode *EXTNAME();
    antlr4::tree::TerminalNode *CATCHTAG();
    antlr4::tree::TerminalNode *AXISUNIT();
    antlr4::tree::TerminalNode *MARK();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TagContext* tag();

  class  FixedNumContext : public antlr4::ParserRuleContext {
  public:
    FixedNumContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *POINTNUM();
    antlr4::tree::TerminalNode *NUM();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FixedNumContext* fixedNum();

  class  GenNumContext : public antlr4::ParserRuleContext {
  public:
    GenNumContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NUM();
    antlr4::tree::TerminalNode *NUMOCT();
    antlr4::tree::TerminalNode *NUMEXT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GenNumContext* genNum();

  class  FeatureFileContext : public antlr4::ParserRuleContext {
  public:
    FeatureFileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<FeatureStatementContext *> featureStatement();
    FeatureStatementContext* featureStatement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FeatureFileContext* featureFile();

  class  StatementFileContext : public antlr4::ParserRuleContext {
  public:
    StatementFileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementFileContext* statementFile();

  class  CvStatementFileContext : public antlr4::ParserRuleContext {
  public:
    CvStatementFileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<CvParameterStatementContext *> cvParameterStatement();
    CvParameterStatementContext* cvParameterStatement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CvStatementFileContext* cvStatementFile();

  class  BaseFileContext : public antlr4::ParserRuleContext {
  public:
    BaseFileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<BaseStatementContext *> baseStatement();
    BaseStatementContext* baseStatement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BaseFileContext* baseFile();

  class  HeadFileContext : public antlr4::ParserRuleContext {
  public:
    HeadFileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<HeadStatementContext *> headStatement();
    HeadStatementContext* headStatement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  HeadFileContext* headFile();

  class  HheaFileContext : public antlr4::ParserRuleContext {
  public:
    HheaFileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<HheaStatementContext *> hheaStatement();
    HheaStatementContext* hheaStatement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  HheaFileContext* hheaFile();

  class  VheaFileContext : public antlr4::ParserRuleContext {
  public:
    VheaFileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<VheaStatementContext *> vheaStatement();
    VheaStatementContext* vheaStatement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VheaFileContext* vheaFile();

  class  GdefFileContext : public antlr4::ParserRuleContext {
  public:
    GdefFileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<GdefStatementContext *> gdefStatement();
    GdefStatementContext* gdefStatement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GdefFileContext* gdefFile();

  class  NameFileContext : public antlr4::ParserRuleContext {
  public:
    NameFileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<NameStatementContext *> nameStatement();
    NameStatementContext* nameStatement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NameFileContext* nameFile();

  class  VmtxFileContext : public antlr4::ParserRuleContext {
  public:
    VmtxFileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<VmtxStatementContext *> vmtxStatement();
    VmtxStatementContext* vmtxStatement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VmtxFileContext* vmtxFile();

  class  Os_2FileContext : public antlr4::ParserRuleContext {
  public:
    Os_2FileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<Os_2StatementContext *> os_2Statement();
    Os_2StatementContext* os_2Statement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Os_2FileContext* os_2File();

  class  StatFileContext : public antlr4::ParserRuleContext {
  public:
    StatFileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<StatStatementContext *> statStatement();
    StatStatementContext* statStatement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatFileContext* statFile();

  class  AxisValueFileContext : public antlr4::ParserRuleContext {
  public:
    AxisValueFileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<AxisValueStatementContext *> axisValueStatement();
    AxisValueStatementContext* axisValueStatement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AxisValueFileContext* axisValueFile();

  class  NameEntryFileContext : public antlr4::ParserRuleContext {
  public:
    NameEntryFileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<NameEntryStatementContext *> nameEntryStatement();
    NameEntryStatementContext* nameEntryStatement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NameEntryFileContext* nameEntryFile();

  class  SubtokContext : public antlr4::ParserRuleContext {
  public:
    SubtokContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SUBSTITUTE();
    antlr4::tree::TerminalNode *SUBSTITUTE_v();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SubtokContext* subtok();

  class  RevtokContext : public antlr4::ParserRuleContext {
  public:
    RevtokContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *REVERSE();
    antlr4::tree::TerminalNode *REVERSE_v();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RevtokContext* revtok();

  class  AnontokContext : public antlr4::ParserRuleContext {
  public:
    AnontokContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ANON();
    antlr4::tree::TerminalNode *ANON_v();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AnontokContext* anontok();

  class  EnumtokContext : public antlr4::ParserRuleContext {
  public:
    EnumtokContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ENUMERATE();
    antlr4::tree::TerminalNode *ENUMERATE_v();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EnumtokContext* enumtok();

  class  PostokContext : public antlr4::ParserRuleContext {
  public:
    PostokContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *POSITION();
    antlr4::tree::TerminalNode *POSITION_v();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PostokContext* postok();

  class  MarkligtokContext : public antlr4::ParserRuleContext {
  public:
    MarkligtokContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *MARKLIG();
    antlr4::tree::TerminalNode *MARKLIG_v();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MarkligtokContext* markligtok();


  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

