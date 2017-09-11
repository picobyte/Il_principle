/*
 * (c) Picobyte 2017, GPL2
 */
#ifndef GENERIC_H
#define GENERIC_H

#include <QPalette>

#define ARRAY_LEN(a) (sizeof(a)/sizeof(*a))

class SimplePalette: public QPalette {
public:
    SimplePalette(const QBrush& normal, const QBrush& disabled, ColorRole CR = WindowText)
    {
        setBrush(Active, CR, QBrush(normal));
        setBrush(Inactive, CR, QBrush(normal));
        setBrush(Disabled, CR, QBrush(disabled));
    }
};

namespace HHStyle {

static const QBrush white = QColor(255, 255, 255, 255);
static const QBrush dark_gray = QColor(25, 25, 25, 255);
static const QBrush bg = QColor(25, 45, 52, 255);
static const QBrush gray = QColor(190, 190, 190, 255);
static const QBrush light_gray = QColor(100, 100, 100, 255);

static const SimplePalette white_text = SimplePalette(white, gray);
static const SimplePalette hdr_text = SimplePalette(gray, dark_gray);

}

class progressStyle: public SimplePalette {
public:
    progressStyle(const QBrush& normal):
        SimplePalette(normal, HHStyle::dark_gray, QPalette::Highlight)
    {}
};

class backgroundStyle: public SimplePalette {
public:
    backgroundStyle(): SimplePalette(HHStyle::white, HHStyle::gray, QPalette::Base)
    {
        setBrush(Active, Window, HHStyle::bg);
        setBrush(Inactive, Window, HHStyle::bg);
        setBrush(Disabled, Window, HHStyle::bg);
    }
};

enum class OutfitType
{
    DefaultOutfit,
    Bathing,
    Casual,
    ClothingItem,
    Club,
    Formal,
    Gym,
    Nude,
    Sleep,
    Swimsuit,
    Work
};

enum class Payperiode
{
    OneTime,
    Daily,
    Weekly,
    Monthly
};

enum class Gender
{
    Male,
    Female,
    Futanari
};

namespace Body {
enum class Part
{
    Anal,
    Breast,
    Penis,
    Stomach,
    Testicle,
    Vagina
};
enum class Size
{
    Flat,
    Tiny,
    VerySmall,
    Small,
    Medium,
    Large,
    Larger,
    Big,
    Huge,
    VeryHuge,
    Gigantic
};
}

enum class SexualPref
{
    Heterosexual,
    Homosexual,
    Bisexual,
    Asexual
};

enum class SchoolSubjectFamily
{
    NONE,
    Mathematics,
    LifeScience,
    NaturalScience,
    SocialScience,
    ComputerStudies,
    Humanities,
    LanguageArts,
    FineArts,
    PhysicalEducation,
    SexualEducation
};

enum class Fetish
{
    Anal,
    BigBreasts,
    BigCocks,
    Bondage,
    Chubby,
    Creampies,
    Crossdressing,
    Cumshots,
    Cunnilingus,
    Defloration,
    Drugs,
    Exhibitionism,
    Fellatio,
    Fingering,
    ForcedSex,
    Futa,
    Glasses,
    GroupSex,
    Hairy,
    Handjobs,
    Kissing,
    Incest,
    Lactation,
    Latex,
    Loli,
    Masochism,
    Masturbation,
    MindControl,
    Muscular,
    Nymphomania,
    Pregnancy,
    Sadism,
    SexToys,
    Shota,
    Swallowing,
    Swimsuits,
    Uniforms,
    Voyeurism,
    Yaoi,
    Yuri,
    None
};

enum class FacialExpressions
{
    Normal,
    Happy,
    Sad,
    Surprised,
    Confused,
    Angry,
    Disgusted,
    Mischievous,
    Resigned,
    Scared,
    Shy,
    Aroused,
    Seductive,
    Ahegao
};

enum class Daylight
{
        Day,
        Night,
        Sunrise,
        Sunset
};

enum class EventDayTypes
{
        All,
        Weekday,
        Weekend,
        Schoolday,
        Monday,
        Tuesday,
        Wednesday,
        Thursday,
        Friday,
        Saturday,
        Sunday
};

/* use Qt::<day> instead.
 * enum class DayOfWeek
{
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday
};*/

enum class RuleStatus
{
    Available,
    ProposalNeeded,
    UpgradeNeeded,
    Blocked
};

enum class Region
{
    City,
    School,
    Business,
    Home
};

enum class PeopleAmount
{
    Empty,
    VerySparse,
    Sparse,
    Normal,
    Crowded,
    VeryCrowded
};

enum class CalendarEntryStatus
{
    Standard,
    Important,
    Holiday,
    Finished
};

#endif // GENERIC_H
