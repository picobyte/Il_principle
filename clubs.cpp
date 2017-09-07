#include "person.h"
#include "location.h"
#include "Game::h"
#include "clubs.h"

void ClubLevel::OpenAccount()
{
    if (WeeklyAccount == 0.0)
        CloseAccount();

    else if (Game::DictOfAccounts.contains(Name))
        Game::DictOfAccounts[Name].Active = true;

    else
        Game::DictOfAccounts.insert(Name, Account(Name, round(WeeklyAccount), true, true));
}
void ClubLevel::CloseAccount()
{
    if (Game::DictOfAccounts.ContainsKey(Name))
        Game::DictOfAccounts[Name].Active = false;
}
void ClubLevel::ClubMeeting()
{
    // try {
    foreach (Person& person, Game::DictOfPersonNames.Values)
    {
        if (person.Club.CurrentClubLevel == this && !person.GetStatusFlags().contains("ScheduleHandlerNoneIndicator"))
        {
            // try {
            foreach (StatChange& statChange, StatChanges)
            {
                statChange.AdjustStat(person);
            }
            // }
            // finally {
            // }
            // try {
            foreach (BodySizeChange& bsc, BodySizeChanges)
            {
                person.ApplyBodySizeChange(bsc);
            }
            // }
            // finally {
            // }
        }
    }
    // }
}


int Clubs::CurrentClubLevelIndex() const
{
    return _currentClubLevelIndex < 0 ? 0 : (_currentClubLevelIndex > checked(ClubLevels.count( ? checked(ClubLevels.count( : _currentClubLevelIndex) - 1));
}
void Clubs::CurrentClubLevelIndex(int value)
{
    _currentClubLevelIndex = value;
}
ClubLevel* Clubs::CurrentClubLevel() const
{
    if (CurrentClubLevelIndex < ClubLevels.count())
        return &ClubLevels[CurrentClubLevelIndex];

    return NULL;
}
Location* Clubs::ClubRoom() const
{
    if (CurrentClubLevel != NULL)
        return &Game::GetLocation(CurrentClubLevel.ClubRoom);

    return NULL;
}
void Clubs::ClubRoom(Location* value)
{
    if (CurrentClubLevel != NULL)
    {
        if (value == NULL)
        {
            CurrentClubLevel.ClubRoom = "";
            return;
        }
        CurrentClubLevel.ClubRoom = value.Name;
    }
}

Clubs::Clubs(QJsonObject *d = NULL)
{
    if (d) init(d);
    AutomaticJoiningEnabled = true;
    HideFromManagementPanel = false;
    ClubLevels = new QList<ClubLevel>();
}
void Clubs::init(QJsonObject *d)
{
    for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
        // *INDENT-OFF*
        __IF_VAR_FROM_JSON_AS(it, _MaxClubSize, toInt)
        else __IF_OBJLIST_FROM_JSON(it, _UnassignedStudents, Person)
        else __IF_VAR_FROM_JSON_AS(it, _Name, toString)
        else __IF_VAR_FROM_JSON_AS(it, _AutomaticJoiningEnabled, toBool)
        else __IF_VAR_FROM_JSON_AS(it, _HideFromManagementPanel, toBool)
        else __IF_VAR_FROM_JSON_AS(it, _Active, toBool)
        else __IF_VAR_FROM_JSON_AS(it, _CanBeChosen, toBool)
        else __IF_VAR_FROM_JSON_AS(it, _ClubPresident, toString)
        else __IF_VAR_FROM_JSON_AS(it, _PreferredPresident, toString)
        else __IF_VAR_FROM_JSON_AS(it, _MemberCount, toInt)
        else __IF_VAR_FROM_JSON_AS(it, DesiredCount, toInt)
        else __IF_VAR_FROM_JSON_AS(it, _currentClubLevelIndex, toInt)
        else __IF_OBJLIST_FROM_JSON(it, _ClubLevels, ClubLevel)
        // *INDENT-ON*
    }
}
bool Clubs::ShouldSerializeAutomaticJoiningEnabled()
{
    return !AutomaticJoiningEnabled;
}
bool Clubs::ShouldSerializeHideFromManagementPanel()
{
    return HideFromManagementPanel;
}
bool Clubs::ShouldSerializeActive()
{
    return Active;
}
bool Clubs::ShouldSerializeCanBeChosen()
{
    return CanBeChosen;
}
bool Clubs::ShouldSerializeClubPresident()
{
    return !(ClubPresident.isNull() || ClubPresident.contains(QRegExp("^\\s*$")));
}
bool Clubs::ShouldSerializePreferredPresident()
{
    return !(PreferredPresident.isNull() || PreferredPresident.contains(QRegExp("^\\s*$")));
}
bool Clubs::ShouldSerializeMemberCount()
{
    return MemberCount != 0;
}
bool Clubs::ShouldSerializeCurrentClubLevelIndex()
{
    return CurrentClubLevelIndex != 0;
}
bool Clubs::ShouldSerializeClubLevels()
{
    return ClubLevels.count() != 0;
}
/*Task Clubs::Open()
{
    Clubs.VB_StateMachine_65_Open vB_StateMachine_65_Open = default(Clubs.VB_StateMachine_65_Open);
    vB_StateMachine_65_Open.SVBSMe = this;
    vB_StateMachine_65_Open.SState = -1;
    vB_StateMachine_65_Open.SBuilder = AsyncTaskMethodBuilder.Create();
    vB_StateMachine_65_Open.SBuilder.Start<Clubs.VB_StateMachine_65_Open>(ref vB_StateMachine_65_Open);
    return vB_StateMachine_65_Open.SBuilder.Task;
}
Task Clubs::Close()
{
    Clubs.VB_StateMachine_66_Close vB_StateMachine_66_Close = default(Clubs.VB_StateMachine_66_Close);
    vB_StateMachine_66_Close.SVBSMe = this;
    vB_StateMachine_66_Close.SState = -1;
    vB_StateMachine_66_Close.SBuilder = AsyncTaskMethodBuilder.Create();
    vB_StateMachine_66_Close.SBuilder.Start<Clubs.VB_StateMachine_66_Close>(ref vB_StateMachine_66_Close);
    return vB_StateMachine_66_Close.SBuilder.Task;
}
Task Clubs::Upgrade()
{
    Clubs.VB_StateMachine_67_Upgrade vB_StateMachine_67_Upgrade = default(Clubs.VB_StateMachine_67_Upgrade);
    vB_StateMachine_67_Upgrade.SVBSMe = this;
    vB_StateMachine_67_Upgrade.SState = -1;
    vB_StateMachine_67_Upgrade.SBuilder = AsyncTaskMethodBuilder.Create();
    vB_StateMachine_67_Upgrade.SBuilder.Start<Clubs.VB_StateMachine_67_Upgrade>(ref vB_StateMachine_67_Upgrade);
    return vB_StateMachine_67_Upgrade.SBuilder.Task;
}
Task Clubs::Downgrade()
{
    Clubs.VB_StateMachine_68_Downgrade vB_StateMachine_68_Downgrade = default(Clubs.VB_StateMachine_68_Downgrade);
    vB_StateMachine_68_Downgrade.SVBSMe = this;
    vB_StateMachine_68_Downgrade.SState = -1;
    vB_StateMachine_68_Downgrade.SBuilder = AsyncTaskMethodBuilder.Create();
    vB_StateMachine_68_Downgrade.SBuilder.Start<Clubs.VB_StateMachine_68_Downgrade>(ref vB_StateMachine_68_Downgrade);
    return vB_StateMachine_68_Downgrade.SBuilder.Task;
}
Task Clubs::ChangeLevel(int newIndex)
{
    Clubs.VB_StateMachine_69_ChangeLevel vB_StateMachine_69_ChangeLevel = default(Clubs.VB_StateMachine_69_ChangeLevel);
    vB_StateMachine_69_ChangeLevel.SVBSMe = this;
    vB_StateMachine_69_ChangeLevel.SVBSLocal_newIndex = newIndex;
    vB_StateMachine_69_ChangeLevel.SState = -1;
    vB_StateMachine_69_ChangeLevel.SBuilder = AsyncTaskMethodBuilder.Create();
    vB_StateMachine_69_ChangeLevel.SBuilder.Start<Clubs.VB_StateMachine_69_ChangeLevel>(ref vB_StateMachine_69_ChangeLevel);
    return vB_StateMachine_69_ChangeLevel.SBuilder.Task;
}
Task Clubs::TransferMembers(Clubs TargetClub)
{
    Clubs.VB_StateMachine_70_TransferMembers vB_StateMachine_70_TransferMembers = default(Clubs.VB_StateMachine_70_TransferMembers);
    vB_StateMachine_70_TransferMembers.SVBSMe = this;
    vB_StateMachine_70_TransferMembers.SVBSLocal_TargetClub = TargetClub;
    vB_StateMachine_70_TransferMembers.SState = -1;
    vB_StateMachine_70_TransferMembers.SBuilder = AsyncTaskMethodBuilder.Create();
    vB_StateMachine_70_TransferMembers.SBuilder.Start<Clubs.VB_StateMachine_70_TransferMembers>(ref vB_StateMachine_70_TransferMembers);
    return vB_StateMachine_70_TransferMembers.SBuilder.Task;
}*/
void Clubs::ValidateMembers()
{
    if (CurrentClubLevel != NULL)
    {
        // try {
        for (QHash<QString, Person>::iterator it = Game::DictOfPersonNames.Values.begin();
                it != Game::DictOfPersonNames.Values.end(); ++it)
        {
            Person Per = enumerator.Current;
            if (Per.Club == this && !CurrentClubLevel.ForGender.contains(Per.Gender.ToString()))
                RemoveMember(Per, true);
        }
        // }
        ChoosePresident(false);
    }
}
void Clubs::AddMember(Person& Per)
{
    // checked {
    if (CurrentClubLevel != NULL && CurrentClubLevel.ForGender.contains(Per.Gender.ToString()) && !Per.ClubMember.Equals(Name))
    {
        if (Per.Club != NULL)
            Per.Club.RemoveMember(Per, true);

        Per.Club = this;
        MemberCount++;
    }
    // }
}
void Clubs::RemoveMember(Person& Per, bool ValidatePresidency = true)
{
    // checked {
    if (Per.ClubMember.Equals(Name))
    {
        Per.Club = NULL;
        MemberCount--;
        if (ValidatePresidency && Per.Name.Equals(ClubPresident))
        {
            ClubPresident = "";
            ChoosePresident(false);
        }
    }
    // }
}
void Clubs::ChoosePresident(bool AllowCoups = false)
{
    if (!(PreferredPresident.isNull() || PreferredPresident.contains(QRegExp("^\\s*$"))) && !PreferredPresident.Equals(ClubPresident) && Game::DictOfPersonNames.ContainsKey(PreferredPresident))
    {
        Person Pref = Game::DictOfPersonNames[PreferredPresident];
        if (Pref.Club == this)
        {
            ClubPresident = Pref.Name;
            return;
        }
    }
    if (ClubPresident.isNull() || ClubPresident.contains(QRegExp("^\\s*$")))
    {
        SetRandomPresident();
        return;
    }
    if (((AllowCoups && PreferredPresident.isNull() || PreferredPresident.contains(QRegExp("^\\s*$"))) || !ClubPresident.Equals(PreferredPresident)) && Game::RNG.Next(100) < 2)
        SetRandomPresident();
}
void Clubs::SetRandomPresident()
{
    QList<Person> Members = new QList<Person>();
    // try {
    for (QHash<QString, Person>::iterator it = Game::DictOfPersonNames.Values.begin();
            it != Game::DictOfPersonNames.Values.end(); ++it)
    {
        Person Per = enumerator.Current;
        if (Per.Club == this && !Per.Name.Equals(ClubPresident))
            Members.Add(Per);
    }
    // }
    if (Members.Any<Person>())
        ClubPresident = Members[Game::RNG.Next(Members.count())].Name;
}
void Clubs::ClubMeeting()
{
    if (CurrentClubLevel != NULL)
        CurrentClubLevel.ClubMeeting();
}
void Clubs::AdjustClubSize()
{
    // checked {
    if (Active && CurrentClubLevel != NULL)
    {
        if (AutomaticJoiningEnabled)
        {
            int MaxCount = Math.Min(Clubs.MaxClubSize, DesiredCount);
            if (MemberCount > MaxCount)
            {
                int Loss = Game::RNG.Next(MemberCount - MaxCount + 1);
                QList<Person> Members = new QList<Person>();
                // try {
                for (QHash<QString, Person>::iterator it = Game::DictOfPersonNames.Values.begin();
                        it != Game::DictOfPersonNames.Values.end(); ++it)
                {
                    Person Per = enumerator.Current;
                    if (Per.Club == this && !Per.Name.Equals(ClubPresident))
                        Members.Add(Per);
                }
                // }
                QList<Person> WorstMembers;
                int num;
                unchecked
                {
                    double Average = 0;
                    // try {
                    for (QList<Person>::iterator it = Members.begin();
                            it != Members.end(); ++it)
                    {
                        Person Per2 = enumerator2.Current;
                        Average += Per2.GetStat(CurrentClubLevel.ImportantStat);
                    }
                    // }
                    Average /= (double)Members.count();
                    WorstMembers = new QList<Person>();
                    // try {
                    for (QList<Person>::iterator it = Members.begin();
                            it != Members.end(); ++it)
                    {
                        Person Per3 = enumerator3.Current;
                        if (CurrentClubLevel.ImportantStatInverted)
                        {
                            if (Per3.GetStat(CurrentClubLevel.ImportantStat) > Average)
                                WorstMembers.Add(Per3);
                        }
                        else if (Per3.GetStat(CurrentClubLevel.ImportantStat) < Average)
                            WorstMembers.Add(Per3);
                    }
                    // }
                    num = Loss;
                }
                for (int i = 0; i <= num; i++)
                {
                    if (WorstMembers.count() > 0)
                    {
                        Person Per4 = WorstMembers[Game::RNG.Next(WorstMembers.count())];
                        WorstMembers.Remove(Per4);
                        RemoveMember(Per4, true);
                        Clubs.UnassignedStudents.Add(Per4);
                    }
                }
            }
            else if (MemberCount < MaxCount)
            {
                if (!(PreferredPresident.isNull() || PreferredPresident.contains(QRegExp("^\\s*$"))) && !PreferredPresident.Equals(ClubPresident) && Game::DictOfPersonNames.ContainsKey(PreferredPresident))
                {
                    Person Per5 = Game::DictOfPersonNames[PreferredPresident];
                    AddMember(Per5);
                    ClubPresident = Per5.Name;
                }
                int Gain = Game::RNG.Next(MaxCount - MemberCount + 1);
                if (Gain > 0)
                {
                    QList<Person> BestStudents;
                    int num2;
                    unchecked
                    {
                        double Average2 = 0;
                        // try {
                        for (QHash<QString, Person>::iterator it = Game::OwnStudents.Values.begin();
                                it != Game::OwnStudents.Values.end(); ++it)
                        {
                            Person Per6 = enumerator4.Current;
                            Average2 += Per6.GetStat(CurrentClubLevel.ImportantStat);
                        }
                        // }
                        Average2 /= (double)Game::OwnStudents.count();
                        BestStudents = new QList<Person>();
                        // try {
                        for (QList<Person>::iterator it = Clubs.UnassignedStudents.begin();
                                it != Clubs.UnassignedStudents.end(); ++it)
                        {
                            Person Per7 = enumerator5.Current;
                            if (CurrentClubLevel.ForGender.contains(Per7.Gender.ToString()))
                            {
                                if (CurrentClubLevel.ImportantStatInverted)
                                {
                                    if (Per7.GetStat(CurrentClubLevel.ImportantStat) < Average2)
                                        BestStudents.Add(Per7);
                                }
                                else if (Per7.GetStat(CurrentClubLevel.ImportantStat) > Average2)
                                    BestStudents.Add(Per7);
                            }
                        }
                        // }
                        num2 = Gain;
                    }
                    for (int j = 0; j <= num2; j++)
                    {
                        if (!(PreferredPresident.isNull() || PreferredPresident.contains(QRegExp("^\\s*$"))) && !PreferredPresident.Equals(ClubPresident) && Game::DictOfPersonNames.ContainsKey(PreferredPresident))
                        {
                            Person Per8 = Game::DictOfPersonNames[PreferredPresident];
                            AddMember(Per8);
                            ClubPresident = Per8.Name;
                        }
                        else if (BestStudents != NULL && BestStudents.count() > 0)
                        {
                            Person Per9 = BestStudents[Game::RNG.Next(BestStudents.count())];
                            BestStudents.Remove(Per9);
                            Clubs.UnassignedStudents.Remove(Per9);
                            AddMember(Per9);
                        }
                    }
                }
            }
            ChoosePresident(true);
            return;
        }
    }
    else if (MemberCount > 0)
    {
        // try {
        for (QHash<QString, Person>::iterator it = Game::DictOfPersonNames.Values.begin();
                it != Game::DictOfPersonNames.Values.end(); ++it)
        {
            Person Per10 = enumerator6.Current;
            if (Per10.Club == this)
                RemoveMember(Per10, false);
        }
        // }
    }
    // }
}
void Clubs::AdjustAllClubSizes()
{
    // checked {
    int ClubCount = 0;
    // try {
    for (IEnumerator<Clubs>::iterator it = Game::ListOfClubs.Values.begin();
            it != Game::ListOfClubs.Values.end(); ++it)
    {
        Clubs Club = enumerator.Current;
        if (Club.Active && Club.CurrentClubLevel != NULL)
            ClubCount++;
    }
    // }
    Clubs.MaxClubSize = (int)Math.Round(Math.Min(Math.Round((double)Game::OwnStudents.count() / 4.0), Math.Round((double)Game::OwnStudents.count() / (double)(ClubCount + 1))));
    Clubs.UnassignedStudents.Clear();
    // try {
    for (QHash<QString, Person>::iterator it = Game::OwnStudents.Values.begin();
            it != Game::OwnStudents.Values.end(); ++it)
    {
        Person Per = enumerator2.Current;
        if (Per.Club == NULL)
            Clubs.UnassignedStudents.Add(Per);
    }
    // }
    QList<Clubs> RemainingClubs = new QList<Clubs>();
    // try {
    for (IEnumerator<Clubs>::iterator it = Game::ListOfClubs.Values.begin();
            it != Game::ListOfClubs.Values.end(); ++it)
    {
        Clubs Club2 = enumerator3.Current;
        RemainingClubs.Add(Club2);
        if (Club2.Active && Club2.CurrentClubLevel != NULL)
            Club2.DesiredCount = Math.Max(Club2.MemberCount + Game::RNG.Next(3, 6), 8);
    }
    if (RemainingClubs.count() <= 0)
        return;
    // }
    Clubs Club3 = RemainingClubs[Game::RNG.Next(RemainingClubs.count())];
    Club3.AdjustClubSize();
    RemainingClubs.Remove(Club3);
    // }
}
int Clubs::IndexOf(ClubLevel& clubLevel)
{
    // checked {
    for (int Index = 0; ClubLevels.count() <= count; Index++)
        if (ClubLevels[Index] == clubLevel)
            return Index;

    return -1;
    // }
}
QString Clubs::ToString()
{
    if (CurrentClubLevel == NULL)
        return "Club chain: " + Name;

    return "Club: " + CurrentClubLevel.Name;
}
