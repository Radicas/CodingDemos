import openai

openai.api_key = "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"

commit_content = "hello"

commit_message = [
    {"role" : "user", "content" : commit_content }
]

response = openai.ChatCompletion.create(
    model = "gpt-3.5-turbo",
    message = commit_message
)
result = response.choices[0].message.content
print(result)
