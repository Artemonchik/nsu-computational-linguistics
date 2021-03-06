#pragma once

#include "WordForm.h"

class Lemma {
private:
    int lemma_id;
    WordForm initial_form;
public:
    const WordForm &getInitialForm() const;

    void setInitialForm(const WordForm &initialForm);

private:
    std::vector<WordForm> forms;

public:
    Lemma(int lemmaId, WordForm initialForm, std::vector<WordForm> forms);

    const std::vector<WordForm> &getForms() const;

    int getId() const;

    std::string str();
};