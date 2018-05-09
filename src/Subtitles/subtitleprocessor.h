/*
 * BDSup2Sub++ (C) 2012 Adam T.
 * Based on code from BDSup2Sub by Copyright 2009 Volker Oth (0xdeadbeef)
 * and Copyright 2012 Miklos Juhasz (mjuhasz)
 *
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SUBTITLEPROCESSOR_H
#define SUBTITLEPROCESSOR_H

#include "Subtitles/bitmap.h"
#include "Subtitles/palette.h"

#include <QByteArray>
#include <QString>
#include <QStringList>
#include <QSharedPointer>
#include <QVector>
#include <QSettings>

class QTextStream;
class Substream;
class SubDVD;
class SupDVD;
class SupXML;
class SupHD;
class SupBD;
class SubPictureDVD;
class SubPicture;
class Filter;

enum class MoveModeX : int;
enum class MoveModeY : int;
enum class OutputMode : int;
enum class InputMode : int;
enum class Resolution : int;
enum class SetState : int;
enum class PaletteMode : int;
enum class ScalingFilters : int;
enum class StreamID : int;
enum class RunType : int;

static QStringList resolutionNamesXml = { "480i", "576i", "720p", "1440x1080", "1080p" };

static QVector<QVector<int>> resolutions = {
    {720, 480},
    {720, 576},
    {1280, 720},
    {1440, 1080},
    {1920, 1080}
};

static QStringList resolutionNames = {
    "NTSC (720x480)",
    "PAL (720x576)",
    "720p (1280x720)",
    "1080p- (1440x1080)",
    "1080p (1920x1080)"
};

static QVector<QVector<QString>> languages = {{
    {"German",       "de", "deu"},
    {"English",      "en", "eng"},
    {"French",       "fr", "fra"},
    {"Italian",      "it", "ita"},
    {"Spanish",      "es", "spa"},
    {"Abkhazian",    "ab", "abk"},
    {"Afar",         "aa", "aar"},
    {"Afrikaans",    "af", "afr"},
    {"Albanian",     "sq", "sqi"},
    {"Amharic",      "am", "amh"},
    {"Arabic",       "ar", "ara"},
    {"Aragonese",    "an", "arg"},
    {"Armenian",     "hy", "hye"},
    {"Assamese",     "as", "asm"},
    {"Avaric",       "av", "ava"},
    {"Avestan",      "ae", "ave"},
    {"Aymara",       "ay", "aym"},
    {"Azerbaijani",  "az", "aze"},
    {"Bambara",      "bm", "bam"},
    {"Bashkir",      "ba", "bak"},
    {"Basque",       "eu", "eus"},
    {"Belarusian",   "be", "bel"},
    {"Bengali",      "bn", "ben"},
    {"Bihari",       "bh", "bih"},
    {"Bislama",      "bi", "bis"},
    {"Bosnian",      "bs", "bos"},
    {"Breton",       "br", "bre"},
    {"Bulgarian",    "bg", "bul"},
    {"Burmese",      "my", "mya"},
    {"Cambodian",    "km", "khm"},
    {"Catalan",      "ca", "cat"},
    {"Chamorro",     "ch", "cha"},
    {"Chechen",      "ce", "che"},
    {"Chichewa",     "ny", "nya"},
    {"Chinese",      "zh", "zho"},
    {"Chuvash",      "cv", "chv"},
    {"Cornish",      "kw", "cor"},
    {"Corsican",     "co", "cos"},
    {"Cree",         "cr", "cre"},
    {"Croatian",     "hr", "hrv"},
    {"Czech",        "cs", "ces"},
    {"Danish",       "da", "dan"},
    {"Divehi",       "dv", "div"},
    {"Dzongkha",     "dz", "dzo"},
    {"Dutch",        "nl", "nld"},
    {"Esperanto",    "eo", "epo"},
    {"Estonian",     "et" ,"est"},
    {"Ewe",          "ee", "ewe"},
    {"Faroese",      "fo", "fao"},
    {"Fiji",         "fj", "fij"},
    {"Finnish",      "fi", "fin"},
    {"Frisian",      "fy", "fry"},
    {"Fulah",        "ff", "ful"},
    {"Gaelic",       "gd", "gla"},
    {"Galician",     "gl", "glg"},
    {"Ganda",        "lg", "lug"},
    {"Georgian",     "ka", "kat"},
    {"Greek",        "el", "ell"},
    {"Greenlandic",  "kl", "kal"},
    {"Guarani",      "gn", "grn"},
    {"Gujarati",     "gu", "guj"},
    {"Haitian",      "ht", "hat"},
    {"Hausa",        "ha", "hau"},
    {"Hebrew",       "he", "heb"},
    {"Herero",       "hz", "her"},
    {"Hindi",        "hi", "hin"},
    {"Hiri Motu",    "ho", "hmo"},
    {"Hungarian",    "hu", "hun"},
    {"Icelandic",    "is", "isl"},
    {"Ido",          "io", "ido"},
    {"Igbo",         "ig", "ibo"},
    {"Indonesian",   "id", "ind"},
    {"Interlingua",  "ia", "ina"},
    {"Interlingue",  "ie", "ile"},
    {"Inupiaq",      "ik", "ipk"},
    {"Inuktitut",    "iu", "iku"},
    {"Irish",        "ga", "gle"},
    {"Japanese",     "ja", "jpn"},
    {"Javanese",     "jv", "jav"},
    {"Kannada",      "kn", "kan"},
    {"Kanuri",       "kr", "kau"},
    {"Kashmiri",     "ks", "kas"},
    {"Kazakh",       "kk", "kaz"},
    {"Kikuyu",       "ki", "kik"},
    {"Kinyarwanda",  "rw", "kin"},
    {"Kirghiz",      "ky", "kir"},
    {"Komi",         "kv", "kom"},
    {"Kongo",        "kg", "kon"},
    {"Korean",       "ko", "kor"},
    {"Kuanyama",     "kj", "kua"},
    {"Kurdish",      "ku", "kur"},
    {"Lao",          "lo", "lao"},
    {"Latin",        "la", "lat"},
    {"Latvian",      "lv", "lav"},
    {"Limburgan",    "li", "lim"},
    {"Lingala",      "ln", "lin"},
    {"Lithuanian",   "lt", "lit"},
    {"Luba",         "lu", "lub"},
    {"Luxembourgish","lb", "ltz"},
    {"Macedonian",   "mk", "mkd"},
    {"Malagasy",     "mg", "mlg"},
    {"Malay",        "ms", "msa"},
    {"Malayalam",    "ml", "mal"},
    {"Maltese",      "mt", "mlt"},
    {"Marshallese",  "mh", "mah"},
    {"Manx",         "gv", "glv"},
    {"Maori",        "mi", "mri"},
    {"Marathi",      "mr", "mar"},
    {"Mongolian",    "mn", "mon"},
    {"Nauru",        "na", "nau"},
    {"Navajo",       "nv", "nav"},
    {"Ndebele",      "nd", "nde"},
    {"Ndonga",       "ng", "ndo"},
    {"Nepali",       "ne", "nep"},
    {"Norwegian",    "no", "nor"},
    {"Occitan",      "oc", "oci"},
    {"Ojibwa",       "oj", "oji"},
    {"Oriya",        "or", "ori"},
    {"Oromo",        "om", "orm"},
    {"Ossetian",     "os", "oss"},
    {"Pali",         "pi", "pli"},
    {"Panjabi",      "pa", "pan"},
    {"Pashto",       "ps", "pus"},
    {"Persian",      "fa", "fas"},
    {"Polish",       "pl", "pol"},
    {"Portuguese",   "pt", "por"},
    {"Quechua",      "qu", "que"},
    {"Romansh",      "rm", "roh"},
    {"Romanian",     "ro", "ron"},
    {"Rundi",        "rn", "run"},
    {"Russian",      "ru", "rus"},
    {"Sami",         "se", "sme"},
    {"Samoan",       "sm", "smo"},
    {"Sango",        "sg", "sag"},
    {"Sanskrit",     "sa", "san"},
    {"Sardinian",    "sc", "srd"},
    {"Serbian",      "sr", "srp"},
    {"Shona",        "sn", "sna"},
    {"Sichuan Yi",   "ii", "iii"},
    {"Sindhi",       "sd", "snd"},
    {"Sinhalese",    "si", "sin"},
    {"Slavonic",     "cu", "chu"},
    {"Slovak",       "sk", "slk"},
    {"Slovenian",    "sl", "slv"},
    {"Somali",       "so", "som"},
    {"Sotho",        "st", "sot"},
    {"Sundanese",    "su", "sun"},
    {"Swahili",      "sw", "swa"},
    {"Swati",        "ss", "ssw"},
    {"Swedish",      "sv", "swe"},
    {"Tagalog",      "tl", "tgl"},
    {"Tahitian",     "ty", "tah"},
    {"Tajik",        "tg", "tgk"},
    {"Tamil",        "ta", "tam"},
    {"Tatar",        "tt", "tar"},
    {"Telugu",       "te", "tel"},
    {"Thai",         "th", "tha"},
    {"Tibetan",      "bo", "bod"},
    {"Tigrinya",     "ti", "tir"},
    {"Tonga",        "to", "ton"},
    {"Tsonga",       "ts", "tso"},
    {"Tswana",       "tn", "tsn"},
    {"Turkish",      "tr", "tur"},
    {"Turkmen",      "tk", "tuk"},
    {"Twi",          "tw", "twi"},
    {"Uighur",       "ug", "uig"},
    {"Ukrainian",    "uk", "ukr"},
    {"Urdu",         "ur", "urd"},
    {"Uzbek",        "uz", "uzb"},
    {"Venda",        "ve", "ven"},
    {"Vietnamese",   "vi", "vie"},
    {"Volapük",     "vo", "vol"},
    {"Welsh",        "cy", "cym"},
    {"Walloon",      "wa", "wln"},
    {"Wolof",        "wo", "wol"},
    {"Xhosa",        "xh", "xho"},
    {"Yiddish",      "yi", "yid"},
    {"Yoruba",       "yo", "yor"},
    {"Zhuang",       "za", "zha"},
    {"Zulu",         "zu", "zul"}
}};

class SubtitleProcessor : public QObject
{
    Q_OBJECT

public:
    SubtitleProcessor(QWidget* parent = 0, QSettings* settings = 0, bool loadSettings = true);
    ~SubtitleProcessor();

    double minScale = 0.5;
    double maxScale = 2.0;

    QWidget* parent;
    QSettings* settings;
    QTextStream* outStream;

    void setOutputStreamToStdError();

    void convertSup(int index, int displayNumber, int displayMax, bool skipScaling = false);
    void setActive(bool value) { isActive = value; }
    QVector<QVector<QString>>& getLanguages() { return languages; }
    Palette &getDefaultDVDPalette() { return defaultDVDPalette; }
    Palette &getCurrentDVDPalette() { return currentDVDPalette; }
    Palette &getCurrentSrcDVDPalette() { return currentSourceDVDPalette; }
    void setCurrentSrcDVDPalette(Palette &value) { currentSourceDVDPalette = value; }
    Palette &getDefaultSrcDVDPalette() { return defaultSourceDVDPalette; }
    void setCineBarFactor(double value) { cineBarFactor = value; }
    int getMoveOffsetX() { return moveOffsetX; }
    void setMoveOffsetX(int value) { moveOffsetX = value; }
    int getMoveOffsetY() { return moveOffsetY; }
    void setMoveOffsetY(int value) { moveOffsetY = value; }
    MoveModeX getMoveModeX() { return moveModeX; }
    void setMoveModeX(MoveModeX value);
    MoveModeY getMoveModeY() { return moveModeY; }
    void setMoveModeY(MoveModeY value);
    int getAlphaCrop() { return alphaCrop; }
    void setAlphaCrop(int value)
    {
        alphaCrop = value;
        if (settings != 0)
        {
            settings->setValue("alphaCrop", QVariant(value));
        }
    }
    bool getFixZeroAlpha() { return fixZeroAlpha; }
    void setFixZeroAlpha(bool value)
    {
        fixZeroAlpha = value;
        if (settings != 0)
        {
            settings->setValue("fixZeroAlpha", QVariant(value));
        }
    }
    int getAlphaThreshold() { return alphaThreshold; }
    bool getVerbatim() { return verbatim; }
    void setVerbatim(bool value)
    {
        verbatim = value;
        if (settings != 0)
        {
            settings->setValue("verbatim", QVariant(value));
        }
    }
    void setAlphaThreshold(int value) { alphaThreshold = value; }
    bool getWritePGCEditPal() { return writePGCEditPal; }
    void setWritePGCEditPal(bool value)
    {
        writePGCEditPal = value;
        if (settings != 0)
        {
            settings->setValue("writePGCEditPal", QVariant(value));
        }
    }
    void setCliMode(bool value) { cliMode = value; }
    bool getExportForced() { return exportForced; }
    void setExportForced(bool value) { exportForced = value; }
    QVector<int> getLuminanceThreshold() { return luminanceThreshold; }
    void setLuminanceThreshold(QVector<int> value) { luminanceThreshold = value; }
    void setLoadPath(QString value) { fileName = value; }
    void setIFOFileName(QString value) { ifoFile = value; }
    int getCropOfsY() { return cropOfsY; }
    int setCropOfsY(int ofs) { return cropOfsY = ofs; }
    OutputMode getOutputMode() { return outMode; }
    void setOutputMode(OutputMode mode);
    InputMode getInputMode() { return inMode; }
    bool getMoveCaptions() { return moveCaptions; }
    void setMoveCaptions(bool value) { moveCaptions = value; }
    bool restoreConvertResolution() { return settings->value("convertResolution", QVariant(convertResolution)).toBool(); }
    bool getConvertResolution() { return convertResolution; }
    void setConvertResolution(bool value) { convertResolution = value; }
    Resolution getOutputResolution() { return resolutionTrg; }
    void setOutputResolution(Resolution value) { resolutionTrg = value; }
    int restoreDelayPTS() { return settings->value("delayPTS", QVariant(delayPTS)).toInt(); }
    int getDelayPTS() { return delayPTS; }
    void setDelayPTS(int value) { delayPTS = value; }
    int getDelayPTSDefault() { return delayPTSdefault; }
    qint64 syncTimePTS(qint64 timeStamp, double fps);
    int restoreMinTimePTS() { return settings->value("minTimePTS", QVariant(minTimePTS)).toInt(); }
    int getMinTimePTS() { return minTimePTS; }
    void setMinTimePTS(int value) { minTimePTS = value; }
    int getMinTimePTSDefault() { return minTimePTSdefault; }
    double restoreFpsTrg() { return settings->value("fpsTrg", QVariant(fpsTrg)).toDouble(); }
    double getFPSTrg() { return fpsTrg; }
    bool restoreConvertFPS() { return settings->value("convertFPS", QVariant(convertFPS)).toBool(); }
    bool getConvertFPS() { return convertFPS; }
    void setConvertFPS(bool value) { convertFPS = value; }
    bool restoreApplyFreeScale() { return settings->value("applyFreeScale", QVariant(applyFreeScale)).toBool(); }
    bool getApplyFreeScale() { return applyFreeScale; }
    void setApplyFreeScale(bool value){ applyFreeScale = value; }
    bool getApplyFreeScaleDefault() { return applyFreeScaleDefault; }
    bool restoreFixShortFrames() { return settings->value("fixShortFrames", QVariant(fixShortFrames)).toBool(); }
    bool getFixShortFrames() { return fixShortFrames; }
    void setFixShortFrames(bool value) { fixShortFrames = value; }
    bool getFixShortFramesDefault() { return fixShortFramesDefault; }
    double restoreFpsSrc() { return settings->value("fpsSrc", QVariant(fpsSrc)).toDouble(); }
    double getFPSSrc() { return fpsSrc; }
    void setFPSSrc(double value, bool fromCLI = false)
    {
        fpsSrc = value;
        if (fromCLI)
        {
            fpsSrcSet = true;
            fpsSrcCertain = true;
        }
    }
    double restoreFreeScaleX() { return settings->value("freeScaleX", QVariant(freeScaleX)).toDouble(); }
    double getFreeScaleX() { return freeScaleX; }
    double restoreFreeScaleY() { return settings->value("freeScaleY", QVariant(freeScaleY)).toDouble(); }
    double getFreeScaleY() { return freeScaleY; }
    SetState getForceAll() { return forceAll; }
    void setForceAll(SetState value) { forceAll = value; }
    void setFreeScale(double x, double y) { freeScaleX = x; freeScaleY = y; }
    bool getFpsSrcCertain() { return fpsSrcCertain; }
    QStringList getRecentFiles() { return recentFiles; }
    PaletteMode getPaletteMode() { return paletteMode; }
    void setPaletteMode(PaletteMode value);
    bool isCancelled() { return !isActive; }
    int getMergePTSdiff() { return mergePTSdiff; }
    void setMergePTSdiff(int value)
    {
        mergePTSdiff = value;
        if (settings != 0)
        {
            settings->setValue("mergePTSdiff", QVariant(value));
        }
    }
    bool usesBT601() { return useBT601; }
    bool getSwapCrCb() { return swapCrCb; }
    void setSwapCrCb(bool value) { swapCrCb = value; }
    ScalingFilters getScalingFilter() { return scalingFilter; }
    void setScalingFilter(ScalingFilters value);
    QString getResolutionName(Resolution res) { return resolutionNames[(int)res]; }
    int getLanguageIdx() { return languageIdx; }
    int getLanguageIdxRead() { return languageIdxRead; }
    void setLanguageIdx(int languageIdx) { this->languageIdx = languageIdx; }
    void setLanguageIdxSet(bool value) { languageIdxSet = value; }
    QString getResolutionNameXml(int idx) { return resolutionNamesXml[idx]; }
    bool getKeepFps() { return keepFps; }
    void setKeepFps(bool value) { keepFps = value; }
    int getErrors() { return numberOfErrors; }
    void resetErrors() { numberOfErrors = 0; }
    int getWarnings() { return numberOfWarnings; }
    void resetWarnings() { numberOfWarnings = 0; }
    void loadedHook() { fpsSrcSet = false; }
    void setIdxToRead(int value) { idxToRead = value; }

    void close();

    void readDVDSubStream(StreamID streamID, bool isVobSub);

    void readXml();
    void readSup();
    void writeSub(QString filename);

    void moveAllToBounds();
    void moveToBounds(SubPicture* picture, int index, double barFactor, int offsetX, int offsetY, MoveModeX moveModeX, MoveModeY moveModeY, int cropOffsetY);

    void scanSubtitles();
    void reScanSubtitles(Resolution oldResolution, double fpsTrgOld, int delayOld,
                         bool convertFpsOld, double fsXOld, double fsYOld);

    void exit();

    int getNumberOfFrames();
    int getNumForcedFrames();
    void addRecent(QString fileName);
    void removeRecent(QString fileName);
    QByteArray getFileID(QString fileName, int numberOfBytes);
    StreamID getStreamID(QByteArray id);
    void setFPSTrg(double trg)
    {
        fpsTrg = trg;
        delayPTS = (int)syncTimePTS(delayPTS, trg);
        minTimePTS = (int)syncTimePTS(minTimePTS, trg);
        if (settings == 0)
        {
            fpsTrgSet = true;
        }
    }
    double getFPS(QString string);
    double getDefaultFPS(Resolution resolution);
    QImage getSrcImage();
    QString getSrcInfoStr(int index);
    QString getTrgInfoStr(int index);
    int getTrgWidth(int index);
    int getTrgHeight(int index);
    int getTrgOfsX(int index);
    int getTrgOfsY(int index);
    QImage getTrgImage();
    int getTrgImgWidth(int index);
    int getTrgImgHeight(int index);
    bool getTrgExcluded(int index);
    Resolution restoreResolution() { return (Resolution)resolutionNames.indexOf(settings->value("resolutionTrg", QVariant(getResolutionName(resolutionTrg))).toString()); }
    Resolution getResolution(int width, int height);
    SubPicture *getSubPictureSrc(int index);
    Resolution getResolution(QString string);
    QVector<int> getResolutions(Resolution resolution);
    QImage getTrgImagePatched(SubPicture* subPicture);
    SubPicture *getSubPictureTrg(int index);
    QVector<int> &getFrameAlpha(int index);
    QVector<int> getOriginalFrameAlpha(int index);
    QVector<int> &getFramePal(int index);
    QVector<int> getOriginalFramePal(int index);
    Filter *scaleFilter;

    void storeFreeScale(double xScale, double yScale);
    void storeSettings();

signals:
    void windowTitleChanged(const QString &newTitle);
    void progressDialogTitleChanged(const QString &newTitle);
    void progressDialogTextChanged(const QString &newText);
    void progressDialogValueChanged(int value);
    void progressDialogVisibilityChanged(bool visible);
    void loadingSubtitleFinished(const QString& errorString);
    void writingSubtitleFinished(const QString& errorString);
    void moveAllFinished(const QString& errorString);
    void printText(const QString &message);
    void addLanguage(const QString &message);

public slots:
    void setMaxProgress(qint64 maxProgress);
    void setCurrentProgress(qint64 currentProgress);
    void readSubtitleStream();
    void createSubtitleStream();
    void moveAll();
    void print(const QString &message);
    void printX(const QString &message);
    void printError(const QString &message);
    void printWarning(const QString &message);
    void onLanguageRead(const QString &message);

private:
    Bitmap trgBitmap;
    Bitmap trgBitmapUnpatched;
    Palette defaultSourceDVDPalette;
    Palette currentSourceDVDPalette;
    Palette trgPal;
    Palette defaultDVDPalette;
    Palette currentDVDPalette;

    QSharedPointer<Substream> substream;
    QSharedPointer<SubDVD> subDVD;
    QSharedPointer<SupDVD> supDVD;
    QSharedPointer<SupXML> supXML;
    QSharedPointer<SupHD> supHD;
    QSharedPointer<SupBD> supBD;

    QStringList recentFiles;

    SubPictureDVD* subVobTrg = 0;

    QVector<SubPicture*> subPictures;

    int languageIdxRead = false;
    int maxProgress = 0;
    double lastProgress = 0.0;
    int numberOfErrors = 0, numberOfWarnings = 0;
    int languageIdx = 0;
    bool languageIdxSet = false;
    int alphaCrop = 14;
    int alphaThreshold = 80;
    int cropOfsY = 0;
    static constexpr int delayPTSdefault = 0;
    int delayPTS = delayPTSdefault;
    static constexpr int minTimePTSdefault = 90 * 500;
    int minTimePTS = minTimePTSdefault;
    int minDim = 8;
    int moveOffsetY = 10;
    int moveOffsetX = 10;
    int numRecent = 5;
    int mergePTSdiff = 18000;
    int idxToRead = -1;
    double fpsSrc;
    double fpsTrg;
    static constexpr double freeScaleXdefault = 1.0;
    double freeScaleX = freeScaleXdefault;
    static constexpr double freeScaleYdefault = 1.0;
    double freeScaleY = freeScaleYdefault;
    double cineBarFactor = 5.0/42;
    bool swapCrCb = false;
    bool fpsSrcCertain = false;
    bool fpsSrcSet = false;
    bool useBT601 = false;
    bool fixZeroAlpha = false;
    bool moveCaptions = false;
    bool cliMode = false;
    bool exportForced = false;
    bool verbatim = false;
    bool verbatimSet = false;
    static constexpr bool applyFreeScaleDefault = false;
    bool applyFreeScale = applyFreeScaleDefault;
    static constexpr bool convertFPSdefault = false;
    bool convertFPS = convertFPSdefault;
    static constexpr bool convertResolutionDefault = false;
    bool convertResolution = convertResolutionDefault;
    static constexpr bool fixShortFramesDefault = false;
    bool fixShortFrames = fixShortFramesDefault;
    bool scalingFilterSet = false;
    bool paletteModeSet = false;
    bool keepFps = false;
    bool fpsTrgSet = false;
    bool writePGCEditPal = false;
    bool writePGCEditPalSet = false;
    PaletteMode paletteMode;
    RunType runType;
    OutputMode outMode;
    bool outModeSet = false;
    InputMode inMode;
    Resolution resolutionTrg;
    SetState forceAll;
    MoveModeY moveModeY;
    MoveModeX moveModeX;
    ScalingFilters scalingFilter;
    bool isActive = false;

    QString fileName = "";
    QString ifoFile = "";
    QVector<int> luminanceThreshold = { 210, 160 };

    QVector<int> alphaDefault = { 0, 0xf, 0xf, 0xf};
    void SetValuesFromSettings();
    int countForcedIncluded();
    int countIncluded();
    void writePGCEditPalette(QString filename, Palette &palette);
    void validateTimes(int index, SubPicture* subPicture, SubPicture* subPictureNext,
                       SubPicture* subPicturePrevious);
    QVector<int> getResolution(Resolution resolution);
    void determineFramePalette(int index);
    bool updateTrgPic(int index);
    QImage getSrcImage(int index);
};

#endif // SUBTITLEPROCESSOR_H
