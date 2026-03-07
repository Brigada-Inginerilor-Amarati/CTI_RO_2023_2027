# Laboratory 5: Recurrent Neural Networks

## 1. Introduction to Recurrent Neural Networks

**Recurrent neural networks (RNNs)** are designed to better handle **sequential information** (time series, speech, text, audio, video, etc.).

RNNs introduce **state variables** to store past information, together with the current inputs, to determine the current outputs.

### Text Preprocessing Steps

When working with text data, the following preprocessing steps are required:

1. **Load text** as strings into memory
2. **Split strings into tokens** (e.g., words and characters)
3. **Build a vocabulary/dictionary** to map the split tokens to numerical indices starting from 0
4. **Convert text into sequences** of numerical indices so they can be manipulated by models easily

---

## 2. Text Preprocessing in PyTorch

### Example: The Time Machine Dataset

The example uses **"The Time Machine"** - a small **corpus** (training set) of just over 30,000 words. The task is **text generation**.

### Step 1: Reading the Dataset

The `read_time_machine()` function reads the dataset into a list of text lines, where each line is a string. For simplicity, punctuation and capitalization are ignored.

```python
def read_time_machine():
    """Load the time machine dataset into a list of text lines."""
    with open(download('http://d2l-data.s3-accelerate.amazonaws.com/timemachine.txt'), 'r') as f:
        lines = f.readlines()
    return [re.sub('[^A-Za-z]+', ' ', line).strip().lower() for line in lines]

lines = read_time_machine()
print(f'# text lines: {len(lines)}')
print(lines[0])
print(lines[10])

# Output:
# text lines: 3221
# the time machine by h g wells
# twinkled and his usually pale face was flushed and animated the
```

### Step 2: Tokenization

The `tokenize()` function takes a list (lines) as the input and splits each text line into a list of tokens.

```python
def tokenize(lines, token='word'):
    """Split text lines into word or character tokens."""
    if token == 'word':
        return [line.split() for line in lines]
    elif token == 'char':
        return [list(line) for line in lines]
    else:
        print('ERROR: unknown token type: ' + token)

tokens = tokenize(lines)
for i in range(11):
    print(tokens[i])

# Output:
# ['the', 'time', 'machine', 'by', 'h', 'g', 'wells']
# []
# []
# []
# ['i']
# []
# []
# ['the', 'time', 'traveller', 'for', 'so', 'it', 'will', 'be', 'convenient', 'to', 'speak', 'of', 'him']
# ['was', 'expounding', 'a', 'recondite', 'matter', 'to', 'us', 'his', 'grey', 'eyes', 'shone', 'and']
# ['twinkled', 'and', 'his', 'usually', 'pale', 'face', 'was', 'flushed', 'and', 'animated', 'the']
```

### Step 3: Building the Vocabulary

The string type of tokens is inconvenient to be used by models, which take numerical inputs.

```python
class Vocab:
    """Vocabulary for text."""
    def __init__(self, tokens=None, min_freq=0, reserved_tokens=None):
        ...

vocab = Vocab(tokens)
print(list(vocab.token_to_idx.items())[:10])

# Output:
# [('<unk>', 0), ('the', 1), ('i', 2), ('and', 3), ('of', 4), ('a', 5), ('to', 6), ('was', 7), ('in', 8), ('that', 9)]
```

Key concepts:

- We first **count the unique tokens** in the corpus and then assign a numerical index to each unique token according to its frequency
- **Rarely appeared tokens** are often removed to reduce complexity
- Any token that does not exist in the corpus or has been removed is mapped into a special **unknown token** `<unk>`
- **Reserved tokens**: `<pad>` (padding), `<bos>` (beginning of a sequence), `<eos>` (end of a sequence)

### Step 4: Loading the Corpus

The `load_corpus_time_machine()` function returns the corpus, a list of token indices, and vocab, the vocabulary of the time machine corpus.

```python
def load_corpus_time_machine(max_tokens=-1):
    """Return token indices and the vocabulary of the time machine dataset."""
    lines = read_time_machine()
    tokens = tokenize(lines, 'char')
    vocab = Vocab(tokens)
    ...
    return corpus, vocab

corpus, vocab = load_corpus_time_machine()
len(corpus), len(vocab)

# Token frequencies
# [(' ', 29927), ('e', 17838), ('t', 13515), ('a', 11704), ('i', 10138), ('n', 9917), ('o', 9758)]
# Token to index
# {'<unk>': 0, ' ': 1, 'e': 2, 't': 3, 'a': 4, 'i': 5, 'n': 6, 'o': 7, 's': 8, 'h': 9, 'r': 10, ...}
# Corpus
# [3, 9, 2, 1, 3, 5, 13, 2, 1, 13, 4, 15, 9, 5, 6, 2, 1, 21, 19, 1, 9, 1, 18, 1, 17, 2, 12, 12, 8]
# (170580, 28)
```

---

## 3. RNN Model

### Architecture

RNNs are neural networks with **hidden states**.

We consider a mini-batch of inputs (**n** sequence examples) **X<sub>t</sub>** ∈ ℝ<sup>n×d</sup> at time step t and denote by **H<sub>t</sub>** ∈ ℝ<sup>n×h</sup> the hidden variable of time step t.

Unlike the MLP, here we save the hidden variable **H<sub>t−1</sub>** from the previous time step and introduce a new weight parameter **W<sub>hh</sub>** ∈ ℝ<sup>h×h</sup> to describe how to use the hidden variable of the previous time step in the current time step.

Specifically, the calculation of the hidden variable of the current time step is determined by the input of the current time step, together with the hidden variable of the previous time step:

**H<sub>t</sub> = φ(X<sub>t</sub>W<sub>xh</sub> + H<sub>t−1</sub>W<sub>hh</sub> + b<sub>h</sub>)** (1)

- **Hidden variable** is called a **hidden state**
- Since the hidden state uses the same definition of the previous time step in the current time step, the computation of (1) is **recurrent**
- Hence, neural networks with hidden states based on recurrent computation are named **recurrent neural networks (RNNs)**
- Layers that perform the computation of (1) in RNNs are called **recurrent layers**

For time step t, the output of the output layer is similar to the computation in the MLP:

**O<sub>t</sub> = H<sub>t</sub>W<sub>hq</sub> + b<sub>q</sub>**

### RNN Parameters

Parameters of the RNN include the weights:

- **W<sub>xh</sub>** ∈ ℝ<sup>d×h</sup>
- **W<sub>hh</sub>** ∈ ℝ<sup>h×h</sup>
- Bias **b<sub>h</sub>** ∈ ℝ<sup>1×h</sup> of the hidden layer

Together with the weights:

- **W<sub>hq</sub>** ∈ ℝ<sup>h×q</sup>
- Bias **b<sub>q</sub>** ∈ ℝ<sup>1×q</sup> of the output layer

**Important**: Even at different time steps, RNNs always use these same model parameters.

Therefore, the **parameterization cost of an RNN does not grow** as the number of time steps increases.

### Computing the Hidden State

At any time step t, the computation of the hidden state can be treated as:

1. **Concatenating** the input **X<sub>t</sub>** at the current time step t and the hidden state **H<sub>t−1</sub>** at the previous time step t-1
2. **Feeding** the concatenation result into a fully-connected layer with the activation function φ

The output of such a fully-connected layer is the hidden state **H<sub>t</sub>** of the current time step t.

In this case, the model parameters are the concatenation of **W<sub>xh</sub>** and **W<sub>hh</sub>**, and a bias of **b<sub>h</sub>**, all from (1).

**H<sub>t</sub>** will also be fed into the fully-connected output layer to compute the output **O<sub>t</sub>** of the current time step t.

---

## 4. RNN in PyTorch

### Implementation

Construct the recurrent neural network layer `rnn_layer` with a single hidden layer and 256 hidden units.

```python
num_hiddens = 256
rnn_layer = nn.RNN(len(vocab), num_hiddens)

class RNNModel(nn.Module):
    """The RNN model."""
    def __init__(self, rnn_layer, vocab_size, **kwargs):
        super(RNNModel, self).__init__(**kwargs)
        self.rnn = rnn_layer
        self.vocab_size = vocab_size
        self.num_hiddens = self.rnn.hidden_size
        self.linear = nn.Linear(self.num_hiddens, self.vocab_size)

    def forward(self, inputs, state):
        X = F.one_hot(inputs.T.long(), self.vocab_size)
        X = X.to(torch.float32)
        Y, state = self.rnn(X, state)
        output = self.linear(Y.reshape((-1, Y.shape[-1])))
        return output, state
    ...

net = RNNModel(rnn_layer, vocab_size=len(vocab))
```

**Key points**:

- Convert tokens into a format that may be fed into ML algorithms using **one-hot encoding**
- The output **Y** of `rnn_layer` refers to the **hidden state at each time step**, and this Y is used as input to the subsequent output layer
- The hidden state is returned by the forward method for later use

---

## 5. Training RNNs

### Gradient Issues

RNN models often need extra help to stabilize the training process because the gradients can be quite large and the optimization algorithm may fail to converge.

An alternative is to **clip the gradient** **g** by projecting it back to a ball of a given radius, say θ, via:

**g ← min(1, θ/||g||) g**

- **Gradient clipping** provides a quick fix to the gradient exploding problem
- The **perplexity** metric is used to measure the quality of a model:

**exp(−(1/n) Σ<sub>t=1</sub><sup>n</sup> log P(x<sub>t</sub>|x<sub>t−1</sub>, ..., x<sub>1</sub>))**

---

## 6. Training RNNs - PyTorch

### Data Loading

```python
def load_data_time_machine(batch_size, num_steps, max_tokens=10000):
    """Return the iterator and the vocabulary of the time machine dataset."""
    data_iter = SeqDataLoader(
        batch_size, num_steps, max_tokens)
    return data_iter, data_iter.vocab

batch_size, num_steps = 32, 35
train_iter, vocab = load_data_time_machine(batch_size, num_steps)
```

**Returns**: Both the data iterator and the vocabulary

- `num_steps` → number of time steps

### Gradient Clipping

```python
def grad_clipping(net, theta):
    """Clip the gradient."""
    params = [p for p in net.parameters() if p.requires_grad]
    norm = torch.sqrt(sum(torch.sum((p.grad ** 2)) for p in params))
    if norm > theta:
        for param in params:
            param.grad[:] *= theta / norm
```

**Clip the gradients** of the model.

### Training Loop

```python
def train(net, train_iter, vocab, lr, num_epochs, device):
    """Train a model."""
    loss = nn.CrossEntropyLoss()
    perplexities = []
    # Initialize
    optimizer = torch.optim.SGD(net.parameters(), lr)
    # Train and predict
    for epoch in range(num_epochs):
        ppl = train_epoch(
            net, train_iter, loss, optimizer, device)
        if (epoch + 1) % 10 == 0:
            print(predict('time traveller', 50, net, vocab, device))
            perplexities.append(ppl)
        print(f'perplexity {ppl:.1f}, device {str(device)}')
        print(predict('time traveller', 50, net, vocab, device))
        print(predict('traveller', 50, net, vocab, device))

    return perplexities

num_epochs, lr = 500, 1
perplexities = train(net, train_iter, vocab, lr, num_epochs, device)

# Output examples:
# time traveller the the the the the the the the the the the the t
# time traveller and the the the the the the the the the the the t
# time traveller the the the the the the the the the the the the t
# time traveller the this the thice some that sime time sion so di
```

---

## 7. Gated Recurrent Units (GRUs)

### Motivation

RNNs may suffer from the **gradient issues** (vanishing gradient or exploding gradient).

To this end, a few specific memory units have been built, namely **Long Short-Term Memory (LSTM)** and **Gated Recurrent Units (GRUs)**.

### GRU Architecture

**GRUs** introduce the **reset gate** and the **update gate**:

- The **reset gate** allows us to control how much of the previous state we might still want to remember
- The **update gate** allows us to control how much of the new state is just a copy of the old state

### Gate Computations

The outputs of the two gates are given by two fully-connected layers with a **sigmoid activation function**.

For a given time step t, the **reset gate R<sub>t</sub>** ∈ ℝ<sup>n×h</sup> and **update gate Z<sub>t</sub>** ∈ ℝ<sup>n×h</sup> are computed as follows:

**R<sub>t</sub> = σ(X<sub>t</sub>W<sub>xr</sub> + H<sub>t−1</sub>W<sub>hr</sub> + b<sub>r</sub>)**

**Z<sub>t</sub> = σ(X<sub>t</sub>W<sub>xz</sub> + H<sub>t−1</sub>W<sub>hz</sub> + b<sub>z</sub>)**

Where:

- **X<sub>t</sub>** ∈ ℝ<sup>n×d</sup> is the input
- **H<sub>t−1</sub>** is the hidden state of the previous time step
- **W<sub>xr</sub>**, **W<sub>xz</sub>** ∈ ℝ<sup>d×h</sup> and **W<sub>hr</sub>**, **W<sub>hz</sub>** ∈ ℝ<sup>h×h</sup> are weight parameters
- **b<sub>r</sub>**, **b<sub>z</sub>** ∈ ℝ<sup>1×h</sup> are biases

### Candidate Hidden State

Integrate **R<sub>t</sub>** in (1) to compute the **candidate hidden state** **H̃<sub>t</sub>** ∈ ℝ<sup>n×h</sup> at time step t:

**H̃<sub>t</sub> = tanh(X<sub>t</sub>W<sub>xh</sub> + (R<sub>t</sub> ⊙ H<sub>t−1</sub>)W<sub>hh</sub> + b<sub>h</sub>)**

Where:

- **W<sub>xh</sub>** ∈ ℝ<sup>d×h</sup> and **W<sub>hh</sub>** ∈ ℝ<sup>h×h</sup> are weight parameters
- **b<sub>h</sub>** ∈ ℝ<sup>1×h</sup> is the bias
- ⊙ represents the **Hadamard product** (element-wise multiplication)

### Final Hidden State

Finally, we incorporate the **update gate Z<sub>t</sub>** to obtain the hidden state at the current time step t:

**H<sub>t</sub> = Z<sub>t</sub> ⊙ H<sub>t−1</sub> + (1 − Z<sub>t</sub>) ⊙ H̃<sub>t</sub>**

This equation shows that:

- When **Z<sub>t</sub> ≈ 1**: the model tends to keep the old state **H<sub>t−1</sub>**
- When **Z<sub>t</sub> ≈ 0**: the new state **H<sub>t</sub>** approaches the candidate hidden state **H̃<sub>t</sub>**

---

## 8. Long Short-Term Memory (LSTM)

### Architecture

The **LSTM** model introduces three gates:

- **Output gate**
- **Input gate**
- **Forget gate**

Just like in GRUs, the data feeding into the LSTM gates are the input at the current time step and the hidden state of the previous time step.

### Gate Equations

Mathematically, the **input gate I<sub>t</sub>**, **forget gate F<sub>t</sub>**, and **output gate O<sub>t</sub>** are computed as follows:

**I<sub>t</sub> = σ(X<sub>t</sub>W<sub>xi</sub> + H<sub>t−1</sub>W<sub>hi</sub> + b<sub>i</sub>)**

**F<sub>t</sub> = σ(X<sub>t</sub>W<sub>xf</sub> + H<sub>t−1</sub>W<sub>hf</sub> + b<sub>f</sub>)**

**O<sub>t</sub> = σ(X<sub>t</sub>W<sub>xo</sub> + H<sub>t−1</sub>W<sub>ho</sub> + b<sub>o</sub>)**

Where:

- **X<sub>t</sub>** ∈ ℝ<sup>n×d</sup> is the input
- **H<sub>t−1</sub>** ∈ ℝ<sup>n×h</sup> is the hidden state at time step t − 1
- **W<sub>xi</sub>**, **W<sub>xf</sub>**, **W<sub>xo</sub>** ∈ ℝ<sup>d×h</sup> and **W<sub>hi</sub>**, **W<sub>hf</sub>**, **W<sub>ho</sub>** ∈ ℝ<sup>h×h</sup> are weight parameters
- **b<sub>i</sub>**, **b<sub>f</sub>**, **b<sub>o</sub>** ∈ ℝ<sup>1×h</sup> are bias parameters

### Candidate Memory Cell

The **candidate memory cell C̃<sub>t</sub>** ∈ ℝ<sup>n×h</sup> is computed as:

**C̃<sub>t</sub> = tanh(X<sub>t</sub>W<sub>xc</sub> + H<sub>t−1</sub>W<sub>hc</sub> + b<sub>c</sub>)**

Where:

- **W<sub>xc</sub>** ∈ ℝ<sup>d×h</sup> and **W<sub>hc</sub>** ∈ ℝ<sup>h×h</sup> are weight parameters
- **b<sub>c</sub>** ∈ ℝ<sup>1×h</sup> is the bias

### Memory Cell and Hidden State

The **memory cell** is computed as:

**C<sub>t</sub> = F<sub>t</sub> ⊙ C<sub>t−1</sub> + I<sub>t</sub> ⊙ C̃<sub>t</sub>**

The **hidden state** in LSTM is given by:

**H<sub>t</sub> = O<sub>t</sub> ⊙ tanh(C<sub>t</sub>)**

---

## 9. Deep Recurrent Neural Networks

Deep RNNs stack multiple recurrent layers on top of each other. The architecture consists of:

- Multiple layers of hidden states at each time step
- Hidden states from layer l-1 feed into layer l at the same time step
- Each layer can capture different levels of abstraction

---

## 10. GRU, LSTM and Deep RNN in PyTorch

### Using GRU Layer

To use a gated recurrent unit:

```python
gru_layer = nn.GRU(num_inputs, num_hiddens)
model = RNNModel(gru_layer, len(vocab))
```

### Using LSTM Layer

To use a long short-term memory:

```python
lstm_layer = nn.LSTM(num_inputs, num_hiddens)
model = RNNModel(lstm_layer, len(vocab))
```

### Deep RNN with Multiple Layers

The `num_layers` parameter specifies the number of recurrent layers:

```python
num_layers = 2
lstm_layer = nn.LSTM(num_inputs, num_hiddens, num_layers)
model = RNNModel(lstm_layer, len(vocab))
```

---

## 11. Sequence to Sequence Learning

### Machine Translation Task

**NLP task**: machine translation

Machine translation datasets are composed of pairs of text sequences that are in the **source language** and the **target language**, respectively.

For this task, the input and the output are both **variable-length sequences**.

### Encoder-Decoder Architecture

**Components**:

- **Encoder**: It takes a variable-length sequence as the input and transforms it into a state with a fixed shape
- **Decoder**: It maps the encoded state of a fixed shape to a variable-length sequence

### Implementation in PyTorch - Data Loading

**English-French dataset** (source language: English, target language: French):

```python
def read_data_nmt():
    """Load the English-French dataset."""
    data_dir = download_extract('http://d2l-data.s3-accelerate.amazonaws.com/fra-eng.zip')
    with open(os.path.join(data_dir, 'fra.txt'), 'r') as f:
        return f.read()

raw_text = read_data_nmt()
print(raw_text[:75])

# Output:
# Go.     Va !
# Hi.     Salut !
# Run!    Cours !
# Run!    Courez !
# Who?    Qui ?
```

**Preprocessing**:

- Word-level tokenization
- Create two vocabularies for both the source language and the target language separately
- Tokens that appear less than 2 times are removed

```python
def load_data_nmt(batch_size, num_steps, num_examples=600):
    """Return the iterator and the vocabularies of the translation dataset."""
    text = preprocess_nmt(read_data_nmt())
    source, target = tokenize_nmt(text, num_examples) # tokens = words
    src_vocab = Vocab(source, min_freq=2,
                      reserved_tokens=['<pad>', '<bos>', '<eos>']) # vocabulary for source language
    tgt_vocab = Vocab(target, min_freq=2,
                      reserved_tokens=['<pad>', '<bos>', '<eos>']) # vocabulary for target language
    src_array, src_valid_len = build_array_nmt(source, src_vocab, num_steps)
    tgt_array, tgt_valid_len = build_array_nmt(target, tgt_vocab, num_steps)
    data_arrays = (src_array, src_valid_len, tgt_array, tgt_valid_len)
    data_iter = load_array(data_arrays, batch_size)
    return data_iter, src_vocab, tgt_vocab
```

### Encoder Implementation

**Model**: Two RNNs are used to design the encoder and the decoder.

```python
class Seq2SeqEncoder(Encoder):
    """The RNN encoder for sequence to sequence learning."""
    def __init__(self, vocab_size, embed_size, num_hiddens, num_layers,
                 dropout=0, **kwargs):
        super(Seq2SeqEncoder, self).__init__(**kwargs)
        # Embedding layer
        self.embedding = nn.Embedding(vocab_size, embed_size)
        self.rnn = nn.GRU(embed_size, num_hiddens, num_layers,
                          dropout=dropout)

    def forward(self, X, *args):
        # The output `X` shape: (`batch_size`, `num_steps`, `embed_size`)
        X = self.embedding(X)
        X = X.permute(1, 0, 2)
        output, state = self.rnn(X)
        # `output` shape: (`num_steps`, `batch_size`, `num_hiddens`)
        # `state` shape: (`num_layers`, `batch_size`, `num_hiddens`)
        return output, state
```

### Decoder Implementation

```python
class Seq2SeqDecoder(Decoder):
    """The RNN decoder for sequence to sequence learning."""
    def __init__(self, vocab_size, embed_size, num_hiddens, num_layers,
                 dropout=0, **kwargs):
        super(Seq2SeqDecoder, self).__init__(**kwargs)
        self.embedding = nn.Embedding(vocab_size, embed_size)
        self.rnn = nn.GRU(embed_size + num_hiddens, num_hiddens, num_layers,
                          dropout=dropout)
        self.dense = nn.Linear(num_hiddens, vocab_size)

    def init_state(self, enc_outputs, *args):
        return enc_outputs[1]

    def forward(self, X, state):
        # The output `X` shape: (`num_steps`, `batch_size`, `embed_size`)
        X = self.embedding(X).permute(1, 0, 2)
        context = state[-1].repeat(X.shape[0], 1, 1)
        X_and_context = torch.cat((X, context), 2)
        output, state = self.rnn(X_and_context, state)
        output = self.dense(output).permute(1, 0, 2)
        return output, state
```

The decoder concatenates the input with the context (encoder's final hidden state) at each time step.

### BLEU Score

**BLEU (Bilingual Evaluation Understudy)** – originally proposed for evaluating machine translation results:

**BLEU = exp(min(0, 1 − len<sub>label</sub>/len<sub>pred</sub>)) ∏<sub>n=1</sub><sup>k</sup> p<sub>n</sub><sup>(1/2)<sup>n</sup></sup>**

Where:

- k is the longest n-grams for matching
- **p<sub>n</sub>** = ratio of the number of matched n-grams in the predicted and label sequences to the number of n-grams in the predicted sequence
- **len<sub>label</sub>** and **len<sub>pred</sub>** = the number of tokens in the label sequence and the predicted sequence, respectively

---

## Summary

This laboratory covered comprehensive concepts related to Recurrent Neural Networks:

1. **RNN Fundamentals**: Understanding sequential information processing and hidden states
2. **Text Preprocessing**: Tokenization, vocabulary building, and data preparation
3. **RNN Architecture**: Hidden state computation, recurrent layers, and parameter sharing
4. **Training Challenges**: Gradient clipping, perplexity metric, and stabilization techniques
5. **Advanced Architectures**: GRU and LSTM for handling long-term dependencies
6. **Deep RNNs**: Stacking multiple recurrent layers
7. **Sequence-to-Sequence Learning**: Encoder-decoder architecture for machine translation

All implementations use PyTorch with practical examples for text generation and machine translation tasks.
