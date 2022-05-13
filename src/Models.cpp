#include "../include/Models.hpp"

std::vector<Model> getModels(OpenCorpaDict* dict) {
    Model model1 =
            {
                    "Moving",
                    {
                            std::make_shared<PropsMatcher>(std::set<std::string>{"NOUN", "anim"}, dict),
                            std::make_shared<WordsMatcher>(
                                    std::vector<std::string>{"идти", "бежать", "пойти", "передвинуться", "гулять"},
                                    dict),
                            std::make_shared<PropsMatcher>(
                                    std::set<std::string>{"PREP"},
                                    dict),
                            std::make_shared<PropsMatcher>(std::set<std::string>{"NOUN"}, dict)
                    }
            };

    Model model2 =
            {
                    "Pray",
                    {
                            std::make_shared<WordsMatcher>(
                                    std::vector<std::string>{"молиться", "молить", "поклоняться", "возлагать",
                                                             "возносить"},
                                    dict),
                            std::make_shared<PropsMatcher>(
                                    std::set<std::string>{"NOUN", "anim"},
                                    dict)
                    }
            };

    Model model3{
            "Hero action",
            {
                    std::make_shared<WordsMatcher>(
                            std::vector<std::string>{"геракл", "персей", "зевс", "тесей", "ахилл"},
                            dict),
                    std::make_shared<PropsMatcher>(
                            std::set<std::string>{"VERB"},
                            dict
                    )
            }
    };

    Model model4{
            "Killing",
            {
                    std::make_shared<WordsMatcher>(
                            std::vector<std::string>{"убить", "убил", "уничтожил", "уничтожить", "казнить",
                                                     "отравить", "отравил"},
                            dict),
                    std::make_shared<PropsMatcher>(
                            std::set<std::string>{"NOUN", "anim"},
                            dict)}
    };

    Model model5{
            "Woman description",
            {std::make_shared<PropsMatcher>(
                    std::set<std::string>{"ADJF"},
                    dict),
             std::make_shared<WordsMatcher>(
                     std::vector<std::string>{"женщина", "дева", "девушка", "жена", "царица", "принцесса"},
                     dict)}
    };

    Model model6{
            "fight",
            {
                    std::make_shared<PropsMatcher>(
                            std::set<std::string>{"NOUN", "anim"},
                            dict),
                    std::make_shared<PropsMatcher>(
                            std::set<std::string>{"VERB"},
                            dict),
                    std::make_shared<AnyMatcher>(),
                    std::make_shared<WordsMatcher>(
                            std::vector<std::string>{"бой", "битва", "сражение", "драка", "война", "убийство"},
                            dict)}
    };

    Model model7{
            "love",
            {
                    std::make_shared<PropsMatcher>(
                            std::set<std::string>{"NOUN", "anim"},
                            dict),
                    std::make_shared<WordsMatcher>(
                            std::vector<std::string>{"любить", "нравиться", "обожать", "влюбиться"},
                            dict),

                    std::make_shared<PropsMatcher>(
                            std::set<std::string>{"NOUN", "anim"},
                            dict)
            }
    };

    Model model8{
            "love",
            {
                    std::make_shared<PropsMatcher>(
                            std::set<std::string>{"NOUN", "anim"},
                            dict),
                    std::make_shared<WordsMatcher>(
                            std::vector<std::string>{"любить", "нравиться", "обожать", "влюбиться"},
                            dict),

                    std::make_shared<PropsMatcher>(
                            std::set<std::string>{"NOUN", "anim"},
                            dict)
            }
    };

    return {model1, model2, model3, model4, model5, model6, model7};
}