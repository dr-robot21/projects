const quiz_container = document.getElementById("quiz_container");
const resultsHtml = document.getElementById("results");
const results_container = document.getElementById("results_container");
const spinner = document.getElementById('spinner')
const timerHtml = document.getElementById("timer");
const scoreHtml = document.getElementById("score");
const questionHtml = document.getElementById("question")
const optionsHtml = document.getElementById("options");
const submitBtn = document.getElementById("submit_answer");



const letters = ['A','B','C','D','E','F','G','H']
let questions = [];
let score = 0;
let timer;
let currentQuestionIndex = 0;
let selectedAnswer = null;
let currentQuestion;
let results = [];
let isQuizFinich = false;


const startSpinner = () => {
    spinner.classList.remove('hidden');
}

const stopSpinner = () => {
    spinner.classList.add('hidden');
}


const loadQuiz = async (url,callback) => {
    startSpinner();
  try {
    const response = await fetch(url);
    
    if (!response.ok) {
      throw new Error('failed to load the quiz');
    }
    
    const data = await response.json();
    questions = data.questions;
    questions.sort(() => Math.random() - 0.5 );
    callback();
    stopSpinner();
    quiz_container.classList.remove('hidden');
    results_container.classList.add('hidden')
    
  } catch (error) {
    console.error('Error fetching data:', error);
  }
}




const createOption = (choice,id) => {
    const option = document.createElement("div");
    const inputID = `input_${id}`;
    option.classList.add('option');
    option.innerHTML = `
        <input type="radio" name="option" id="${inputID}">
        <label for="${inputID}">
            <span class="option-letter">${letters[id]}</span>
            ${choice}
        </label>
    `
    option.onclick = () => {
        selectedAnswer = choice;
    }
    optionsHtml.appendChild(option);
}


const loadQuestion = () => {
    clearInterval(timer);
    let time = 30;
    let current = questions[currentQuestionIndex];
    currentQuestion = current;
    timerHtml.textContent = "00:"+time;
    questionHtml.innerHTML = `<strong>Question ${currentQuestionIndex+1} : </strong> ${current.question}`;
    optionsHtml.innerHTML = '';

    current.options.sort(() => Math.random() - 0.5 );
    current.options.forEach( (option,index) => {
        createOption(option,index);
    })
    timer = setInterval(()=> {
        time--;
        timerHtml.textContent = time < 10 ? "00:0"+time : "00:"+time;

        if(time <= 0) {
            clearInterval(timer);
            nextQuestion();
        }
    },1000)
}

const showResults = () => {
    clearInterval(timer);
    quiz_container.classList.add('hidden');
    results_container.classList.remove('hidden');
    scoreHtml.textContent = `Score: ${score}/${questions.length}`;

    results.forEach( (result,index) => {
        resultsHtml.innerHTML += `
                <div class="result">
                    <h3 class="question"><strong>Question ${index + 1} : </strong>${result.question}</h3>
                    <p class="user-answer">
                        <strong>Your answer :</strong>
                        ${result.userAnswer}
                    </p>
                        <p class="user-answer">
                        <strong>Correct answer :</strong>
                        ${result.correctAnswer}
                    </p>
                </div>
        `
    })
}


const isCorrectAnswer = (answer) => {
    return answer === currentQuestion.correctAnswer;
}

const nextQuestion =()=> {
    if(selectedAnswer !== null && !isQuizFinich && isCorrectAnswer(selectedAnswer)) {
        score++;
    }
    results.push(
        {
            question:currentQuestion.question,
            userAnswer:selectedAnswer,
            correctAnswer:currentQuestion.correctAnswer
        }
    )
    selectedAnswer = null;

    currentQuestionIndex++;
    if(currentQuestionIndex < questions.length) {
        loadQuestion();
    }else {
        showResults();
        isQuizFinich = true;
    }
}

const displayQuestions = () => {
    loadQuestion();
    submitBtn.addEventListener('click',nextQuestion);
}

loadQuiz("questions.json",displayQuestions);